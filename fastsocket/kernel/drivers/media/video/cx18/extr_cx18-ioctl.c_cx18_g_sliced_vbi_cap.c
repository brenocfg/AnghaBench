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
struct v4l2_sliced_vbi_cap {scalar_t__ type; int service_set; int** service_lines; scalar_t__* reserved; } ;
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {scalar_t__ is_50hz; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_SLICED_VBI_CAPTURE ; 
 int V4L2_SLICED_VBI_525 ; 
 int V4L2_SLICED_VBI_625 ; 
 scalar_t__ valid_service_line (int,int,scalar_t__) ; 

__attribute__((used)) static int cx18_g_sliced_vbi_cap(struct file *file, void *fh,
					struct v4l2_sliced_vbi_cap *cap)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;
	int set = cx->is_50hz ? V4L2_SLICED_VBI_625 : V4L2_SLICED_VBI_525;
	int f, l;

	if (cap->type != V4L2_BUF_TYPE_SLICED_VBI_CAPTURE)
		return -EINVAL;

	cap->service_set = 0;
	for (f = 0; f < 2; f++) {
		for (l = 0; l < 24; l++) {
			if (valid_service_line(f, l, cx->is_50hz)) {
				/*
				 * We can find all v4l2 supported vbi services
				 * for the standard, on a valid line for the std
				 */
				cap->service_lines[f][l] = set;
				cap->service_set |= set;
			} else
				cap->service_lines[f][l] = 0;
		}
	}
	for (f = 0; f < 3; f++)
		cap->reserved[f] = 0;
	return 0;
}