#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; int xmin; int ymin; int xmax; int ymax; TYPE_1__* avctx; } ;
struct TYPE_6__ {int width; int height; scalar_t__ out_format; int mb_width; int mb_height; scalar_t__ unrestricted_mv; TYPE_3__ me; } ;
struct TYPE_5__ {int me_range; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ MotionEstContext ;

/* Variables and functions */
 void* FFMAX (int,int) ; 
 void* FFMIN (int,int) ; 
 int FLAG_QPEL ; 
 scalar_t__ FMT_H261 ; 
 int MAX_MV ; 

__attribute__((used)) static inline void get_limits(MpegEncContext *s, int x, int y)
{
    MotionEstContext * const c= &s->me;
    int range= c->avctx->me_range >> (1 + !!(c->flags&FLAG_QPEL));
    int max_range = MAX_MV >> (1 + !!(c->flags&FLAG_QPEL));
/*
    if(c->avctx->me_range) c->range= c->avctx->me_range >> 1;
    else                   c->range= 16;
*/
    if (s->unrestricted_mv) {
        c->xmin = - x - 16;
        c->ymin = - y - 16;
        c->xmax = - x + s->width;
        c->ymax = - y + s->height;
    } else if (s->out_format == FMT_H261){
        // Search range of H.261 is different from other codec standards
        c->xmin = (x > 15) ? - 15 : 0;
        c->ymin = (y > 15) ? - 15 : 0;
        c->xmax = (x < s->mb_width * 16 - 16) ? 15 : 0;
        c->ymax = (y < s->mb_height * 16 - 16) ? 15 : 0;
    } else {
        c->xmin = - x;
        c->ymin = - y;
        c->xmax = - x + s->mb_width *16 - 16;
        c->ymax = - y + s->mb_height*16 - 16;
    }
    if(!range || range > max_range)
        range = max_range;
    if(range){
        c->xmin = FFMAX(c->xmin,-range);
        c->xmax = FFMIN(c->xmax, range);
        c->ymin = FFMAX(c->ymin,-range);
        c->ymax = FFMIN(c->ymax, range);
    }
}