#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  qpel_mc_func ;
typedef  int /*<<< orphan*/  op_pixels_func ;
struct TYPE_4__ {scalar_t__ out_format; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ FMT_MPEG1 ; 
 int /*<<< orphan*/  mpv_motion_internal (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 

void ff_mpv_motion(MpegEncContext *s,
                   uint8_t *dest_y, uint8_t *dest_cb,
                   uint8_t *dest_cr, int dir,
                   uint8_t **ref_picture,
                   op_pixels_func (*pix_op)[4],
                   qpel_mc_func (*qpix_op)[16])
{
#if !CONFIG_SMALL
    if (s->out_format == FMT_MPEG1)
        mpv_motion_internal(s, dest_y, dest_cb, dest_cr, dir,
                            ref_picture, pix_op, qpix_op, 1);
    else
#endif
        mpv_motion_internal(s, dest_y, dest_cb, dest_cr, dir,
                            ref_picture, pix_op, qpix_op, 0);
}