#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct soc_camera_host {TYPE_1__* ops; } ;
struct soc_camera_format_xlate {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {unsigned int num_user_formats; TYPE_2__* user_formats; TYPE_2__* current_fmt; TYPE_6__ dev; } ;
typedef  enum v4l2_mbus_pixelcode { ____Placeholder_v4l2_mbus_pixelcode } v4l2_mbus_pixelcode ;
struct TYPE_8__ {int code; int /*<<< orphan*/  host_fmt; } ;
struct TYPE_7__ {int (* get_formats ) (struct soc_camera_device*,unsigned int,TYPE_2__*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  dev_dbg (TYPE_6__*,char*,unsigned int) ; 
 int /*<<< orphan*/  enum_mbus_fmt ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 int /*<<< orphan*/  soc_mbus_get_fmtdesc (int) ; 
 int stub1 (struct soc_camera_device*,unsigned int,TYPE_2__*) ; 
 int stub2 (struct soc_camera_device*,unsigned int,TYPE_2__*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int*) ; 
 int /*<<< orphan*/  vfree (TYPE_2__*) ; 
 int /*<<< orphan*/  video ; 
 TYPE_2__* vmalloc (unsigned int) ; 

__attribute__((used)) static int soc_camera_init_user_formats(struct soc_camera_device *icd)
{
	struct v4l2_subdev *sd = soc_camera_to_subdev(icd);
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	unsigned int i, fmts = 0, raw_fmts = 0;
	int ret;
	enum v4l2_mbus_pixelcode code;

	while (!v4l2_subdev_call(sd, video, enum_mbus_fmt, raw_fmts, &code))
		raw_fmts++;

	if (!ici->ops->get_formats)
		/*
		 * Fallback mode - the host will have to serve all
		 * sensor-provided formats one-to-one to the user
		 */
		fmts = raw_fmts;
	else
		/*
		 * First pass - only count formats this host-sensor
		 * configuration can provide
		 */
		for (i = 0; i < raw_fmts; i++) {
			ret = ici->ops->get_formats(icd, i, NULL);
			if (ret < 0)
				return ret;
			fmts += ret;
		}

	if (!fmts)
		return -ENXIO;

	icd->user_formats =
		vmalloc(fmts * sizeof(struct soc_camera_format_xlate));
	if (!icd->user_formats)
		return -ENOMEM;

	icd->num_user_formats = fmts;

	dev_dbg(&icd->dev, "Found %d supported formats.\n", fmts);

	/* Second pass - actually fill data formats */
	fmts = 0;
	for (i = 0; i < raw_fmts; i++)
		if (!ici->ops->get_formats) {
			v4l2_subdev_call(sd, video, enum_mbus_fmt, i, &code);
			icd->user_formats[i].host_fmt =
				soc_mbus_get_fmtdesc(code);
			icd->user_formats[i].code = code;
		} else {
			ret = ici->ops->get_formats(icd, i,
						    &icd->user_formats[fmts]);
			if (ret < 0)
				goto egfmt;
			fmts += ret;
		}

	icd->current_fmt = &icd->user_formats[0];

	return 0;

egfmt:
	icd->num_user_formats = 0;
	vfree(icd->user_formats);
	return ret;
}