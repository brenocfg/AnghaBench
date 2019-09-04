#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* prefetch ) (int /*<<< orphan*/ *,int,int) ;} ;
struct TYPE_5__ {int const*** mv; int mb_x; int mb_y; int const linesize; int const uvlinesize; TYPE_1__ vdsp; scalar_t__ quarter_sample; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int const,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void prefetch_motion(MpegEncContext *s, uint8_t **pix, int dir)
{
    /* fetch pixels for estimated mv 4 macroblocks ahead
     * optimized for 64byte cache lines */
    const int shift = s->quarter_sample ? 2 : 1;
    const int mx    = (s->mv[dir][0][0] >> shift) + 16 * s->mb_x + 8;
    const int my    = (s->mv[dir][0][1] >> shift) + 16 * s->mb_y;
    int off         = mx + (my + (s->mb_x & 3) * 4) * s->linesize + 64;

    s->vdsp.prefetch(pix[0] + off, s->linesize, 4);
    off = (mx >> 1) + ((my >> 1) + (s->mb_x & 7)) * s->uvlinesize + 64;
    s->vdsp.prefetch(pix[1] + off, pix[2] - pix[1], 2);
}