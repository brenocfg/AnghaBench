#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_fmtdesc {int index; } ;
struct vpfe_pixel_format {struct v4l2_fmtdesc fmtdesc; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ (* enum_pix ) (int /*<<< orphan*/ *,int) ;} ;
struct TYPE_4__ {TYPE_1__ hw_ops; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* ccdc_dev ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 struct vpfe_pixel_format* vpfe_lookup_pix_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpfe_enum_fmt_vid_cap(struct file *file, void  *priv,
				   struct v4l2_fmtdesc *fmt)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);
	const struct vpfe_pixel_format *pix_fmt;
	int temp_index;
	u32 pix;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_enum_fmt_vid_cap\n");

	if (ccdc_dev->hw_ops.enum_pix(&pix, fmt->index) < 0)
		return -EINVAL;

	/* Fill in the information about format */
	pix_fmt = vpfe_lookup_pix_format(pix);
	if (NULL != pix_fmt) {
		temp_index = fmt->index;
		*fmt = pix_fmt->fmtdesc;
		fmt->index = temp_index;
		return 0;
	}
	return -EINVAL;
}