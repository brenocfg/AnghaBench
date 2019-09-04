#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_12__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_25__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_1__* dst; } ;
struct TYPE_24__ {int quality; int* linesize; int** data; } ;
struct TYPE_23__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_22__ {int qp; int parity; TYPE_12__* enc_ctx; } ;
struct TYPE_21__ {TYPE_5__** outputs; TYPE_2__* priv; } ;
struct TYPE_20__ {TYPE_4__* coded_frame; } ;
typedef  TYPE_2__ MCDeintContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFABS (int) ; 
 int FF_QP2LAMBDA ; 
 int av_clip (int,int,int) ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int avcodec_encode_video2 (TYPE_12__*,TYPE_3__*,TYPE_4__*,int*) ; 
 int ff_filter_frame (TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* ff_get_video_buffer (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *inpic)
{
    MCDeintContext *mcdeint = inlink->dst->priv;
    AVFilterLink *outlink = inlink->dst->outputs[0];
    AVFrame *outpic, *frame_dec;
    AVPacket pkt = {0};
    int x, y, i, ret, got_frame = 0;

    outpic = ff_get_video_buffer(outlink, outlink->w, outlink->h);
    if (!outpic) {
        av_frame_free(&inpic);
        return AVERROR(ENOMEM);
    }
    av_frame_copy_props(outpic, inpic);
    inpic->quality = mcdeint->qp * FF_QP2LAMBDA;

    av_init_packet(&pkt);

    ret = avcodec_encode_video2(mcdeint->enc_ctx, &pkt, inpic, &got_frame);
    if (ret < 0)
        goto end;

    frame_dec = mcdeint->enc_ctx->coded_frame;

    for (i = 0; i < 3; i++) {
        int is_chroma = !!i;
        int w = AV_CEIL_RSHIFT(inlink->w, is_chroma);
        int h = AV_CEIL_RSHIFT(inlink->h, is_chroma);
        int fils = frame_dec->linesize[i];
        int srcs = inpic    ->linesize[i];
        int dsts = outpic   ->linesize[i];

        for (y = 0; y < h; y++) {
            if ((y ^ mcdeint->parity) & 1) {
                for (x = 0; x < w; x++) {
                    uint8_t *filp = &frame_dec->data[i][x + y*fils];
                    uint8_t *srcp = &inpic    ->data[i][x + y*srcs];
                    uint8_t *dstp = &outpic   ->data[i][x + y*dsts];

                    if (y > 0 && y < h-1){
                        int is_edge = x < 3 || x > w-4;
                        int diff0 = filp[-fils] - srcp[-srcs];
                        int diff1 = filp[+fils] - srcp[+srcs];
                        int temp = filp[0];

#define DELTA(j) av_clip(j, -x, w-1-x)

#define GET_SCORE_EDGE(j)\
   FFABS(srcp[-srcs+DELTA(-1+(j))] - srcp[+srcs+DELTA(-1-(j))])+\
   FFABS(srcp[-srcs+DELTA(j)     ] - srcp[+srcs+DELTA(  -(j))])+\
   FFABS(srcp[-srcs+DELTA(1+(j)) ] - srcp[+srcs+DELTA( 1-(j))])

#define GET_SCORE(j)\
   FFABS(srcp[-srcs-1+(j)] - srcp[+srcs-1-(j)])+\
   FFABS(srcp[-srcs  +(j)] - srcp[+srcs  -(j)])+\
   FFABS(srcp[-srcs+1+(j)] - srcp[+srcs+1-(j)])

#define CHECK_EDGE(j)\
    {   int score = GET_SCORE_EDGE(j);\
        if (score < spatial_score){\
            spatial_score = score;\
            diff0 = filp[-fils+DELTA(j)]    - srcp[-srcs+DELTA(j)];\
            diff1 = filp[+fils+DELTA(-(j))] - srcp[+srcs+DELTA(-(j))];\

#define CHECK(j)\
    {   int score = GET_SCORE(j);\
        if (score < spatial_score){\
            spatial_score= score;\
            diff0 = filp[-fils+(j)] - srcp[-srcs+(j)];\
            diff1 = filp[+fils-(j)] - srcp[+srcs-(j)];\

                        if (is_edge) {
                            int spatial_score = GET_SCORE_EDGE(0) - 1;
                            CHECK_EDGE(-1) CHECK_EDGE(-2) }} }}
                            CHECK_EDGE( 1) CHECK_EDGE( 2) }} }}
                        } else {
                            int spatial_score = GET_SCORE(0) - 1;
                            CHECK(-1) CHECK(-2) }} }}
                            CHECK( 1) CHECK( 2) }} }}
                        }


                        if (diff0 + diff1 > 0)
                            temp -= (diff0 + diff1 - FFABS(FFABS(diff0) - FFABS(diff1)) / 2) / 2;
                        else
                            temp -= (diff0 + diff1 + FFABS(FFABS(diff0) - FFABS(diff1)) / 2) / 2;
                        *filp = *dstp = temp > 255U ? ~(temp>>31) : temp;
                    } else {
                        *dstp = *filp;
                    }
                }
            }
        }

        for (y = 0; y < h; y++) {
            if (!((y ^ mcdeint->parity) & 1)) {
                for (x = 0; x < w; x++) {
                    frame_dec->data[i][x + y*fils] =
                    outpic   ->data[i][x + y*dsts] = inpic->data[i][x + y*srcs];
                }
            }
        }
    }
    mcdeint->parity ^= 1;

end:
    av_packet_unref(&pkt);
    av_frame_free(&inpic);
    if (ret < 0) {
        av_frame_free(&outpic);
        return ret;
    }
    return ff_filter_frame(outlink, outpic);
}