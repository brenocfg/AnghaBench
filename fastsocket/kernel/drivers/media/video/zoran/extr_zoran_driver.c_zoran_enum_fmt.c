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
struct zoran {int dummy; } ;
struct v4l2_fmtdesc {int /*<<< orphan*/  flags; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  description; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  fourcc; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NUM_FORMATS ; 
 int /*<<< orphan*/  V4L2_FMT_FLAG_COMPRESSED ; 
 int ZORAN_FORMAT_COMPRESSED ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* zoran_formats ; 

__attribute__((used)) static int zoran_enum_fmt(struct zoran *zr, struct v4l2_fmtdesc *fmt, int flag)
{
	unsigned int num, i;

	for (num = i = 0; i < NUM_FORMATS; i++) {
		if (zoran_formats[i].flags & flag && num++ == fmt->index) {
			strncpy(fmt->description, zoran_formats[i].name,
				sizeof(fmt->description) - 1);
			/* fmt struct pre-zeroed, so adding '\0' not neeed */
			fmt->pixelformat = zoran_formats[i].fourcc;
			if (zoran_formats[i].flags & ZORAN_FORMAT_COMPRESSED)
				fmt->flags |= V4L2_FMT_FLAG_COMPRESSED;
			return 0;
		}
	}
	return -EINVAL;
}