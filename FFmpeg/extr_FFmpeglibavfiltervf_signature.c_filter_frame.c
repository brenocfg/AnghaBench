#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_23__ {int /*<<< orphan*/ * outputs; TYPE_3__* priv; } ;
struct TYPE_22__ {int w; int h; TYPE_8__* dst; } ;
struct TYPE_21__ {int** data; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  pts; } ;
struct TYPE_20__ {int elem_count; int left_count; int block_count; int /*<<< orphan*/ * blocks; scalar_t__ av_elem; } ;
struct TYPE_19__ {int* framesig; int* words; int /*<<< orphan*/  confidence; scalar_t__ index; int /*<<< orphan*/  pts; struct TYPE_19__* prev; struct TYPE_19__* next; } ;
struct TYPE_18__ {TYPE_2__* streamcontexts; } ;
struct TYPE_17__ {int coarsecount; int midcoarse; TYPE_1__* curcoarsesig2; TYPE_1__* curcoarsesig1; TYPE_1__* coarseend; scalar_t__ divide; int /*<<< orphan*/  lastindex; TYPE_4__* finesiglist; TYPE_4__* curfinesig; } ;
struct TYPE_16__ {TYPE_4__* last; int /*<<< orphan*/ * data; struct TYPE_16__* next; TYPE_4__* first; } ;
typedef  TYPE_2__ StreamContext ;
typedef  TYPE_3__ SignatureContext ;
typedef  TYPE_4__ FineSignature ;
typedef  TYPE_5__ ElemCat ;
typedef  int /*<<< orphan*/  CoarseSignature ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVFilterLink ;
typedef  TYPE_8__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_LOG_DEBUG ; 
 int BLOCK_LCM ; 
 int DIFFELEM_SIZE ; 
 int ELEMENT_COUNT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFABS (int) ; 
 int /*<<< orphan*/  FFMIN (int,int) ; 
 size_t FF_INLINK_IDX (TYPE_7__*) ; 
 int SIGELEM_SIZE ; 
 int /*<<< orphan*/  av_freep (int**) ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,scalar_t__,char*,...) ; 
 scalar_t__ av_log_get_level () ; 
 int* av_malloc_array (int,int) ; 
 void* av_mallocz (int) ; 
 scalar_t__ cmp ; 
 TYPE_5__** elements ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ get_block_size (int /*<<< orphan*/ *) ; 
 scalar_t__ get_block_sum (TYPE_2__*,int**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qsort (int*,int,int,void*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *picref)
{
    AVFilterContext *ctx = inlink->dst;
    SignatureContext *sic = ctx->priv;
    StreamContext *sc = &(sic->streamcontexts[FF_INLINK_IDX(inlink)]);
    FineSignature* fs;

    static const uint8_t pot3[5] = { 3*3*3*3, 3*3*3, 3*3, 3, 1 };
    /* indexes of words : 210,217,219,274,334  44,175,233,270,273  57,70,103,237,269  100,285,295,337,354  101,102,111,275,296
    s2usw = sorted to unsorted wordvec: 44 is at index 5, 57 at index 10...
    */
    static const unsigned int wordvec[25] = {44,57,70,100,101,102,103,111,175,210,217,219,233,237,269,270,273,274,275,285,295,296,334,337,354};
    static const uint8_t      s2usw[25]   = { 5,10,11, 15, 20, 21, 12, 22,  6,  0,  1,  2,  7, 13, 14,  8,  9,  3, 23, 16, 17, 24,  4, 18, 19};

    uint8_t wordt2b[5] = { 0, 0, 0, 0, 0 }; /* word ternary to binary */
    uint64_t intpic[32][32];
    uint64_t rowcount;
    uint8_t *p = picref->data[0];
    int inti, intj;
    int *intjlut;

    uint64_t conflist[DIFFELEM_SIZE];
    int f = 0, g = 0, w = 0;
    int32_t dh1 = 1, dh2 = 1, dw1 = 1, dw2 = 1, a, b;
    int64_t denom;
    int i, j, k, ternary;
    uint64_t blocksum;
    int blocksize;
    int64_t th; /* threshold */
    int64_t sum;

    int64_t precfactor = (sc->divide) ? 65536 : BLOCK_LCM;

    /* initialize fs */
    if (sc->curfinesig) {
        fs = av_mallocz(sizeof(FineSignature));
        if (!fs)
            return AVERROR(ENOMEM);
        sc->curfinesig->next = fs;
        fs->prev = sc->curfinesig;
        sc->curfinesig = fs;
    } else {
        fs = sc->curfinesig = sc->finesiglist;
        sc->curcoarsesig1->first = fs;
    }

    fs->pts = picref->pts;
    fs->index = sc->lastindex++;

    memset(intpic, 0, sizeof(uint64_t)*32*32);
    intjlut = av_malloc_array(inlink->w, sizeof(int));
    if (!intjlut)
        return AVERROR(ENOMEM);
    for (i = 0; i < inlink->w; i++) {
        intjlut[i] = (i*32)/inlink->w;
    }

    for (i = 0; i < inlink->h; i++) {
        inti = (i*32)/inlink->h;
        for (j = 0; j < inlink->w; j++) {
            intj = intjlut[j];
            intpic[inti][intj] += p[j];
        }
        p += picref->linesize[0];
    }
    av_freep(&intjlut);

    /* The following calculates a summed area table (intpic) and brings the numbers
     * in intpic to the same denominator.
     * So you only have to handle the numinator in the following sections.
     */
    dh1 = inlink->h / 32;
    if (inlink->h % 32)
        dh2 = dh1 + 1;
    dw1 = inlink->w / 32;
    if (inlink->w % 32)
        dw2 = dw1 + 1;
    denom = (sc->divide) ? dh1 * dh2 * dw1 * dw2 : 1;

    for (i = 0; i < 32; i++) {
        rowcount = 0;
        a = 1;
        if (dh2 > 1) {
            a = ((inlink->h*(i+1))%32 == 0) ? (inlink->h*(i+1))/32 - 1 : (inlink->h*(i+1))/32;
            a -= ((inlink->h*i)%32 == 0) ? (inlink->h*i)/32 - 1 : (inlink->h*i)/32;
            a = (a == dh1)? dh2 : dh1;
        }
        for (j = 0; j < 32; j++) {
            b = 1;
            if (dw2 > 1) {
                b = ((inlink->w*(j+1))%32 == 0) ? (inlink->w*(j+1))/32 - 1 : (inlink->w*(j+1))/32;
                b -= ((inlink->w*j)%32 == 0) ? (inlink->w*j)/32 - 1 : (inlink->w*j)/32;
                b = (b == dw1)? dw2 : dw1;
            }
            rowcount += intpic[i][j] * a * b * precfactor / denom;
            if (i > 0) {
                intpic[i][j] = intpic[i-1][j] + rowcount;
            } else {
                intpic[i][j] = rowcount;
            }
        }
    }

    denom = (sc->divide) ? 1 : dh1 * dh2 * dw1 * dw2;

    for (i = 0; i < ELEMENT_COUNT; i++) {
        const ElemCat* elemcat = elements[i];
        int64_t* elemsignature;
        uint64_t* sortsignature;

        elemsignature = av_malloc_array(elemcat->elem_count, sizeof(int64_t));
        if (!elemsignature)
            return AVERROR(ENOMEM);
        sortsignature = av_malloc_array(elemcat->elem_count, sizeof(int64_t));
        if (!sortsignature) {
            av_freep(&elemsignature);
            return AVERROR(ENOMEM);
        }

        for (j = 0; j < elemcat->elem_count; j++) {
            blocksum = 0;
            blocksize = 0;
            for (k = 0; k < elemcat->left_count; k++) {
                blocksum += get_block_sum(sc, intpic, &elemcat->blocks[j*elemcat->block_count+k]);
                blocksize += get_block_size(&elemcat->blocks[j*elemcat->block_count+k]);
            }
            sum = blocksum / blocksize;
            if (elemcat->av_elem) {
                sum -= 128 * precfactor * denom;
            } else {
                blocksum = 0;
                blocksize = 0;
                for (; k < elemcat->block_count; k++) {
                    blocksum += get_block_sum(sc, intpic, &elemcat->blocks[j*elemcat->block_count+k]);
                    blocksize += get_block_size(&elemcat->blocks[j*elemcat->block_count+k]);
                }
                sum -= blocksum / blocksize;
                conflist[g++] = FFABS(sum * 8 / (precfactor * denom));
            }

            elemsignature[j] = sum;
            sortsignature[j] = FFABS(sum);
        }

        /* get threshold */
        qsort(sortsignature, elemcat->elem_count, sizeof(uint64_t), (void*) cmp);
        th = sortsignature[(int) (elemcat->elem_count*0.333)];

        /* ternarize */
        for (j = 0; j < elemcat->elem_count; j++) {
            if (elemsignature[j] < -th) {
                ternary = 0;
            } else if (elemsignature[j] <= th) {
                ternary = 1;
            } else {
                ternary = 2;
            }
            fs->framesig[f/5] += ternary * pot3[f%5];

            if (f == wordvec[w]) {
                fs->words[s2usw[w]/5] += ternary * pot3[wordt2b[s2usw[w]/5]++];
                if (w < 24)
                    w++;
            }
            f++;
        }
        av_freep(&elemsignature);
        av_freep(&sortsignature);
    }

    /* confidence */
    qsort(conflist, DIFFELEM_SIZE, sizeof(uint64_t), (void*) cmp);
    fs->confidence = FFMIN(conflist[DIFFELEM_SIZE/2], 255);

    /* coarsesignature */
    if (sc->coarsecount == 0) {
        if (sc->curcoarsesig2) {
            sc->curcoarsesig1 = av_mallocz(sizeof(CoarseSignature));
            if (!sc->curcoarsesig1)
                return AVERROR(ENOMEM);
            sc->curcoarsesig1->first = fs;
            sc->curcoarsesig2->next = sc->curcoarsesig1;
            sc->coarseend = sc->curcoarsesig1;
        }
    }
    if (sc->coarsecount == 45) {
        sc->midcoarse = 1;
        sc->curcoarsesig2 = av_mallocz(sizeof(CoarseSignature));
        if (!sc->curcoarsesig2)
            return AVERROR(ENOMEM);
        sc->curcoarsesig2->first = fs;
        sc->curcoarsesig1->next = sc->curcoarsesig2;
        sc->coarseend = sc->curcoarsesig2;
    }
    for (i = 0; i < 5; i++) {
        set_bit(sc->curcoarsesig1->data[i], fs->words[i]);
    }
    /* assuming the actual frame is the last */
    sc->curcoarsesig1->last = fs;
    if (sc->midcoarse) {
        for (i = 0; i < 5; i++) {
            set_bit(sc->curcoarsesig2->data[i], fs->words[i]);
        }
        sc->curcoarsesig2->last = fs;
    }

    sc->coarsecount = (sc->coarsecount+1)%90;

    /* debug printing finesignature */
    if (av_log_get_level() == AV_LOG_DEBUG) {
        av_log(ctx, AV_LOG_DEBUG, "input %d, confidence: %d\n", FF_INLINK_IDX(inlink), fs->confidence);

        av_log(ctx, AV_LOG_DEBUG, "words:");
        for (i = 0; i < 5; i++) {
            av_log(ctx, AV_LOG_DEBUG, " %d:", fs->words[i] );
            av_log(ctx, AV_LOG_DEBUG, " %d", fs->words[i] / pot3[0] );
            for (j = 1; j < 5; j++)
                av_log(ctx, AV_LOG_DEBUG, ",%d", fs->words[i] % pot3[j-1] / pot3[j] );
            av_log(ctx, AV_LOG_DEBUG, ";");
        }
        av_log(ctx, AV_LOG_DEBUG, "\n");

        av_log(ctx, AV_LOG_DEBUG, "framesignature:");
        for (i = 0; i < SIGELEM_SIZE/5; i++) {
            av_log(ctx, AV_LOG_DEBUG, " %d", fs->framesig[i] / pot3[0] );
            for (j = 1; j < 5; j++)
                av_log(ctx, AV_LOG_DEBUG, ",%d", fs->framesig[i] % pot3[j-1] / pot3[j] );
        }
        av_log(ctx, AV_LOG_DEBUG, "\n");
    }

    if (FF_INLINK_IDX(inlink) == 0)
        return ff_filter_frame(inlink->dst->outputs[0], picref);
    return 1;
}