#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct ov7670_win_size {unsigned char com7_bit; TYPE_1__* regs; int /*<<< orphan*/  vstop; int /*<<< orphan*/  vstart; int /*<<< orphan*/  hstop; int /*<<< orphan*/  hstart; } ;
struct ov7670_info {unsigned char clkrc; struct ov7670_format_struct* fmt; } ;
struct ov7670_format_struct {TYPE_1__* regs; } ;
struct TYPE_2__ {unsigned char value; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CLKRC ; 
 int /*<<< orphan*/  REG_COM7 ; 
 int /*<<< orphan*/  ov7670_set_hw (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ov7670_try_fmt_internal (struct v4l2_subdev*,struct v4l2_mbus_framefmt*,struct ov7670_format_struct**,struct ov7670_win_size**) ; 
 int ov7670_write (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned char) ; 
 int ov7670_write_array (struct v4l2_subdev*,TYPE_1__*) ; 
 struct ov7670_info* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7670_s_mbus_fmt(struct v4l2_subdev *sd,
			  struct v4l2_mbus_framefmt *fmt)
{
	struct ov7670_format_struct *ovfmt;
	struct ov7670_win_size *wsize;
	struct ov7670_info *info = to_state(sd);
	unsigned char com7;
	int ret;

	ret = ov7670_try_fmt_internal(sd, fmt, &ovfmt, &wsize);

	if (ret)
		return ret;
	/*
	 * COM7 is a pain in the ass, it doesn't like to be read then
	 * quickly written afterward.  But we have everything we need
	 * to set it absolutely here, as long as the format-specific
	 * register sets list it first.
	 */
	com7 = ovfmt->regs[0].value;
	com7 |= wsize->com7_bit;
	ov7670_write(sd, REG_COM7, com7);
	/*
	 * Now write the rest of the array.  Also store start/stops
	 */
	ov7670_write_array(sd, ovfmt->regs + 1);
	ov7670_set_hw(sd, wsize->hstart, wsize->hstop, wsize->vstart,
			wsize->vstop);
	ret = 0;
	if (wsize->regs)
		ret = ov7670_write_array(sd, wsize->regs);
	info->fmt = ovfmt;

	/*
	 * If we're running RGB565, we must rewrite clkrc after setting
	 * the other parameters or the image looks poor.  If we're *not*
	 * doing RGB565, we must not rewrite clkrc or the image looks
	 * *really* poor.
	 *
	 * (Update) Now that we retain clkrc state, we should be able
	 * to write it unconditionally, and that will make the frame
	 * rate persistent too.
	 */
	if (ret == 0)
		ret = ov7670_write(sd, REG_CLKRC, info->clkrc);
	return 0;
}