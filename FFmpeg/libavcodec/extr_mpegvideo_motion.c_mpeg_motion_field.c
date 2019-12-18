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
typedef  int /*<<< orphan*/  op_pixels_func ;
struct TYPE_4__ {scalar_t__ out_format; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ FMT_MPEG1 ; 
 int /*<<< orphan*/  mpeg_motion_internal (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int,int,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mpeg_motion_field(MpegEncContext *s, uint8_t *dest_y,
                              uint8_t *dest_cb, uint8_t *dest_cr,
                              int bottom_field, int field_select,
                              uint8_t **ref_picture,
                              op_pixels_func (*pix_op)[4],
                              int motion_x, int motion_y, int h, int mb_y)
{
#if !CONFIG_SMALL
    if (s->out_format == FMT_MPEG1)
        mpeg_motion_internal(s, dest_y, dest_cb, dest_cr, 1,
                             bottom_field, field_select, ref_picture, pix_op,
                             motion_x, motion_y, h, 1, 0, mb_y);
    else
#endif
        mpeg_motion_internal(s, dest_y, dest_cb, dest_cr, 1,
                             bottom_field, field_select, ref_picture, pix_op,
                             motion_x, motion_y, h, 0, 0, mb_y);
}