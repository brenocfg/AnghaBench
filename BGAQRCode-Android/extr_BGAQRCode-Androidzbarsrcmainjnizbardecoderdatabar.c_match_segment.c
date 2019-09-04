#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_11__ {unsigned int csegs; int epoch; TYPE_2__* segs; } ;
struct TYPE_9__ {int direction; int /*<<< orphan*/  modifiers; TYPE_3__ databar; } ;
typedef  TYPE_1__ zbar_decoder_t ;
struct TYPE_10__ {int count; scalar_t__ finder; scalar_t__ color; scalar_t__ side; int check; int epoch; unsigned int data; int /*<<< orphan*/  width; scalar_t__ partial; scalar_t__ exp; } ;
typedef  TYPE_2__ databar_segment_t ;
typedef  TYPE_3__ databar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_DATABAR ; 
 int /*<<< orphan*/  ZBAR_MOD_GS1 ; 
 int /*<<< orphan*/  ZBAR_PARTIAL ; 
 scalar_t__ acquire_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  databar_postprocess (TYPE_1__*,unsigned int*) ; 
 int /*<<< orphan*/  dbprintf (int,char*,int,unsigned int,unsigned int,...) ; 
 scalar_t__ size_buf (TYPE_1__*,int) ; 

__attribute__((used)) static inline zbar_symbol_type_t
match_segment (zbar_decoder_t *dcode,
               databar_segment_t *seg)
{
    databar_decoder_t *db = &dcode->databar;
    unsigned csegs = db->csegs, maxage = 0xfff;
    int i0, i1, i2, maxcnt = 0;
    databar_segment_t *smax[3] = { NULL, };

    if(seg->partial && seg->count < 4)
        return(ZBAR_PARTIAL);

    for(i0 = 0; i0 < csegs; i0++) {
        databar_segment_t *s0 = db->segs + i0;
        if(s0 == seg || s0->finder != seg->finder || s0->exp ||
           s0->color != seg->color || s0->side == seg->side ||
           (s0->partial && s0->count < 4) ||
           !check_width(seg->width, s0->width, 14))
            continue;

        for(i1 = 0; i1 < csegs; i1++) {
            databar_segment_t *s1 = db->segs + i1;
            int chkf, chks, chk;
            unsigned age1;
            if(i1 == i0 || s1->finder < 0 || s1->exp ||
               s1->color == seg->color ||
               (s1->partial && s1->count < 4) ||
               !check_width(seg->width, s1->width, 14))
                continue;
            dbprintf(2, "\n\t[%d,%d] f=%d(0%xx)/%d(%x%x%x)",
                     i0, i1, seg->finder, seg->color,
                     s1->finder, s1->exp, s1->color, s1->side);

            if(seg->color)
                chkf = seg->finder + s1->finder * 9;
            else
                chkf = s1->finder + seg->finder * 9;
            if(chkf > 72)
                chkf--;
            if(chkf > 8)
                chkf--;

            chks = (seg->check + s0->check + s1->check) % 79;

            if(chkf >= chks)
                chk = chkf - chks;
            else
                chk = 79 + chkf - chks;

            dbprintf(2, " chk=(%d,%d) => %d", chkf, chks, chk);
            age1 = (((db->epoch - s0->epoch) & 0xff) +
                    ((db->epoch - s1->epoch) & 0xff));

            for(i2 = i1 + 1; i2 < csegs; i2++) {
                databar_segment_t *s2 = db->segs + i2;
                unsigned cnt, age2, age;
                if(i2 == i0 || s2->finder != s1->finder || s2->exp ||
                   s2->color != s1->color || s2->side == s1->side ||
                   s2->check != chk ||
                   (s2->partial && s2->count < 4) ||
                   !check_width(seg->width, s2->width, 14))
                    continue;
                age2 = (db->epoch - s2->epoch) & 0xff;
                age = age1 + age2;
                cnt = s0->count + s1->count + s2->count;
                dbprintf(2, " [%d] MATCH cnt=%d age=%d", i2, cnt, age);
                if(maxcnt < cnt ||
                   (maxcnt == cnt && maxage > age)) {
                    maxcnt = cnt;
                    maxage = age;
                    smax[0] = s0;
                    smax[1] = s1;
                    smax[2] = s2;
                }
            }
        }
    }

    if(!smax[0])
        return(ZBAR_PARTIAL);

    unsigned d[4];
    d[(seg->color << 1) | seg->side] = seg->data;
    for(i0 = 0; i0 < 3; i0++) {
        d[(smax[i0]->color << 1) | smax[i0]->side] = smax[i0]->data;
        if(!--(smax[i0]->count))
            smax[i0]->finder = -1;
    }
    seg->finder = -1;

    if(size_buf(dcode, 18))
        return(ZBAR_PARTIAL);

    if(acquire_lock(dcode, ZBAR_DATABAR))
        return(ZBAR_PARTIAL);

    databar_postprocess(dcode, d);
    dcode->modifiers = MOD(ZBAR_MOD_GS1);
    dcode->direction = 1 - 2 * (seg->side ^ seg->color ^ 1);
    return(ZBAR_DATABAR);
}