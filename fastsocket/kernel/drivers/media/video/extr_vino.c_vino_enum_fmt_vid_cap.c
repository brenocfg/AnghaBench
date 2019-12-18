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
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  description; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;
struct TYPE_2__ {size_t description; int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t VINO_DATA_FMT_COUNT ; 
 int /*<<< orphan*/  dprintk (char*,size_t) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* vino_data_formats ; 

__attribute__((used)) static int vino_enum_fmt_vid_cap(struct file *file, void *__fh,
			      struct v4l2_fmtdesc *fd)
{
	dprintk("format index = %d\n", fd->index);

	if (fd->index >= VINO_DATA_FMT_COUNT)
		return -EINVAL;
	dprintk("format name = %s\n", vino_data_formats[fd->index].description);

	fd->pixelformat = vino_data_formats[fd->index].pixelformat;
	strcpy(fd->description, vino_data_formats[fd->index].description);
	return 0;
}