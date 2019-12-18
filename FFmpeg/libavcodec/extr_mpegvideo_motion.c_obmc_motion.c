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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  op_pixels_func ;
typedef  scalar_t__ int16_t ;
struct TYPE_5__ {int /*<<< orphan*/ * obmc_scratchpad; } ;
struct TYPE_6__ {scalar_t__ quarter_sample; int linesize; TYPE_1__ sc; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 size_t MID ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  hpel_motion (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  put_obmc (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static inline void obmc_motion(MpegEncContext *s,
                               uint8_t *dest, uint8_t *src,
                               int src_x, int src_y,
                               op_pixels_func *pix_op,
                               int16_t mv[5][2] /* mid top left right bottom */)
#define MID    0
{
    int i;
    uint8_t *ptr[5];

    av_assert2(s->quarter_sample == 0);

    for (i = 0; i < 5; i++) {
        if (i && mv[i][0] == mv[MID][0] && mv[i][1] == mv[MID][1]) {
            ptr[i] = ptr[MID];
        } else {
            ptr[i] = s->sc.obmc_scratchpad + 8 * (i & 1) +
                     s->linesize * 8 * (i >> 1);
            hpel_motion(s, ptr[i], src, src_x, src_y, pix_op,
                        mv[i][0], mv[i][1]);
        }
    }

    put_obmc(dest, ptr, s->linesize);
}