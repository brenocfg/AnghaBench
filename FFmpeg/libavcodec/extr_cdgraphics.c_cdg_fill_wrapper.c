#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdg_copy_rect_buf (int,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  cdg_fill_rect_preset (int,int,int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static void cdg_fill_wrapper(int out_tl_x, int out_tl_y, uint8_t *out,
                             int in_tl_x, int in_tl_y, uint8_t *in,
                             int color, int w, int h, int stride, int roll)
{
    if (roll) {
        cdg_copy_rect_buf(out_tl_x, out_tl_y, out, in_tl_x, in_tl_y,
                          in, w, h, stride);
    } else {
        cdg_fill_rect_preset(out_tl_x, out_tl_y, out, color, w, h, stride);
    }
}