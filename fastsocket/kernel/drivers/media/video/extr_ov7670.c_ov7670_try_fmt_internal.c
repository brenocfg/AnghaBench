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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct ov7670_win_size {scalar_t__ width; scalar_t__ height; } ;
struct ov7670_format_struct {scalar_t__ mbus_code; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int N_OV7670_FMTS ; 
 int N_WIN_SIZES ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct ov7670_format_struct* ov7670_formats ; 
 struct ov7670_win_size* ov7670_win_sizes ; 

__attribute__((used)) static int ov7670_try_fmt_internal(struct v4l2_subdev *sd,
		struct v4l2_mbus_framefmt *fmt,
		struct ov7670_format_struct **ret_fmt,
		struct ov7670_win_size **ret_wsize)
{
	int index;
	struct ov7670_win_size *wsize;

	for (index = 0; index < N_OV7670_FMTS; index++)
		if (ov7670_formats[index].mbus_code == fmt->code)
			break;
	if (index >= N_OV7670_FMTS) {
		/* default to first format */
		index = 0;
		fmt->code = ov7670_formats[0].mbus_code;
	}
	if (ret_fmt != NULL)
		*ret_fmt = ov7670_formats + index;
	/*
	 * Fields: the OV devices claim to be progressive.
	 */
	fmt->field = V4L2_FIELD_NONE;
	/*
	 * Round requested image size down to the nearest
	 * we support, but not below the smallest.
	 */
	for (wsize = ov7670_win_sizes; wsize < ov7670_win_sizes + N_WIN_SIZES;
	     wsize++)
		if (fmt->width >= wsize->width && fmt->height >= wsize->height)
			break;
	if (wsize >= ov7670_win_sizes + N_WIN_SIZES)
		wsize--;   /* Take the smallest one */
	if (ret_wsize != NULL)
		*ret_wsize = wsize;
	/*
	 * Note the size we'll actually handle.
	 */
	fmt->width = wsize->width;
	fmt->height = wsize->height;
	fmt->colorspace = ov7670_formats[index].colorspace;
	return 0;
}