#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int finder; scalar_t__ exp; scalar_t__ color; scalar_t__ side; scalar_t__ data; scalar_t__ check; int width; unsigned int count; int epoch; int /*<<< orphan*/  partial; } ;
typedef  TYPE_1__ databar_segment_t ;
struct TYPE_6__ {unsigned int csegs; int epoch; TYPE_1__* segs; } ;
typedef  TYPE_2__ databar_decoder_t ;

/* Variables and functions */
 scalar_t__ check_width (int,int,int) ; 
 int /*<<< orphan*/  dbprintf (int,char*,int,unsigned int,int) ; 

__attribute__((used)) static inline void
merge_segment (databar_decoder_t *db,
               databar_segment_t *seg)
{
    unsigned csegs = db->csegs;
    int i;
    for(i = 0; i < csegs; i++) {
        databar_segment_t *s = db->segs + i;
        if(s != seg && s->finder == seg->finder && s->exp == seg->exp &&
           s->color == seg->color && s->side == seg->side &&
           s->data == seg->data && s->check == seg->check &&
           check_width(seg->width, s->width, 14)) {
            /* merge with existing segment */
            unsigned cnt = s->count;
            if(cnt < 0x7f)
                cnt++;
            seg->count = cnt;
            seg->partial &= s->partial;
            seg->width = (3 * seg->width + s->width + 2) / 4;
            s->finder = -1;
            dbprintf(2, " dup@%d(%d,%d)",
                     i, cnt, (db->epoch - seg->epoch) & 0xff);
        }
        else if(s->finder >= 0) {
            unsigned age = (db->epoch - s->epoch) & 0xff;
            if(age >= 248 || (age >= 128 && s->count < 2))
                s->finder = -1;
        }
    }
}