#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_13__ {unsigned int csegs; int epoch; TYPE_2__* segs; } ;
struct TYPE_11__ {int direction; int /*<<< orphan*/  modifiers; TYPE_3__ databar; } ;
typedef  TYPE_1__ zbar_decoder_t ;
struct TYPE_12__ {unsigned int width; char finder; int count; int color; int side; int epoch; unsigned int data; scalar_t__ check; int /*<<< orphan*/  partial; scalar_t__ exp; } ;
typedef  TYPE_2__ databar_segment_t ;
typedef  TYPE_3__ databar_decoder_t ;

/* Variables and functions */
 int DATABAR_MAX_SEGMENTS ; 
 int IDX (TYPE_2__*) ; 
 int /*<<< orphan*/  MOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_DATABAR_EXP ; 
 int /*<<< orphan*/  ZBAR_MOD_GS1 ; 
 int /*<<< orphan*/  ZBAR_PARTIAL ; 
 scalar_t__ acquire_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_width (unsigned int,unsigned int,int) ; 
 scalar_t__ databar_postprocess_exp (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int /*<<< orphan*/  lookup_sequence (TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  release_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline zbar_symbol_type_t
match_segment_exp (zbar_decoder_t *dcode,
                   databar_segment_t *seg,
                   int dir)
{
    databar_decoder_t *db = &dcode->databar;
    int bestsegs[22], i = 0, segs[22], seq[22];
    int ifixed = seg - db->segs, fixed = IDX(seg), maxcnt = 0;
    int iseg[DATABAR_MAX_SEGMENTS];
    unsigned csegs = db->csegs, width = seg->width, maxage = 0x7fff;

    bestsegs[0] = segs[0] = seq[1] = -1;
    seq[0] = 0;

    dbprintf(2, "\n    fixed=%d@%d: ", fixed, ifixed);
    for(i = csegs, seg = db->segs + csegs - 1; --i >= 0; seg--) {
        if(seg->exp && seg->finder >= 0 &&
           (!seg->partial || seg->count >= 4))
            iseg[i] = IDX(seg);
        else
            iseg[i] = -1;
        dbprintf(2, " %d", iseg[i]);
    }

    for(i = 0; ; i--) {
        if(!i)
            dbprintf(2, "\n   ");
        for(; i >= 0 && seq[i] >= 0; i--) {
            int j;
            dbprintf(2, " [%d]%d", i, seq[i]);

            if(seq[i] == fixed) {
                seg = db->segs + ifixed;
                if(segs[i] < 0 && check_width(width, seg->width, 14)) {
                    dbprintf(2, "*");
                    j = ifixed;
                }
                else
                    continue;
            }
            else {
                for(j = segs[i] + 1; j < csegs; j++) {
                    if(iseg[j] == seq[i] &&
                       (!i || check_width(width, db->segs[j].width, 14))) {
                        seg = db->segs + j;
                        break;
                    }
                }
                if(j == csegs)
                    continue;
            }

            if(!i) {
                if(!lookup_sequence(seg, fixed, seq)) {
                    dbprintf(2, "[nf]");
                    continue;
                }
                width = seg->width;
                dbprintf(2, " A00@%d", j);
            }
            else {
                width = (width + seg->width) / 2;
                dbprintf(2, " %c%x%x@%d",
                         'A' + seg->finder, seg->color, seg->side, j);
            }
            segs[i++] = j;
            segs[i++] = -1;
        }
        if(i < 0)
            break;

        seg = db->segs + segs[0];
        unsigned cnt = 0, chk = 0, age = (db->epoch - seg->epoch) & 0xff;
        for(i = 1; segs[i] >= 0; i++) {
            seg = db->segs + segs[i];
            chk += seg->check;
            cnt += seg->count;
            age += (db->epoch - seg->epoch) & 0xff;
        }

        unsigned data0 = db->segs[segs[0]].data;
        unsigned chk0 = data0 % 211;
        chk %= 211;

        dbprintf(2, " chk=%d ?= %d", chk, chk0);
        if(chk != chk0)
            continue;

        dbprintf(2, " cnt=%d age=%d", cnt, age);
        if(maxcnt > cnt || (maxcnt == cnt && maxage <= age))
            continue;

        dbprintf(2, " !");
        maxcnt = cnt;
        maxage = age;
        for(i = 0; segs[i] >= 0; i++)
            bestsegs[i] = segs[i];
        bestsegs[i] = -1;
    }

    if(bestsegs[0] < 0)
        return(ZBAR_PARTIAL);

    if(acquire_lock(dcode, ZBAR_DATABAR_EXP))
        return(ZBAR_PARTIAL);

    for(i = 0; bestsegs[i] >= 0; i++)
        segs[i] = db->segs[bestsegs[i]].data;

    if(databar_postprocess_exp(dcode, segs)) {
        release_lock(dcode, ZBAR_DATABAR_EXP);
        return(ZBAR_PARTIAL);
    }

    for(i = 0; bestsegs[i] >= 0; i++)
        if(bestsegs[i] != ifixed) {
            seg = db->segs + bestsegs[i];
            if(!--seg->count)
                seg->finder = -1;
        }

    /* FIXME stacked rows are frequently reversed,
     * so direction is impossible to determine at this level
     */
    dcode->direction = (1 - 2 * (seg->side ^ seg->color)) * dir;
    dcode->modifiers = MOD(ZBAR_MOD_GS1);
    return(ZBAR_DATABAR_EXP);
}