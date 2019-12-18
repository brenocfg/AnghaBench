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
struct videobuf_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_VBI (char*) ; 
 int vbi_pixel_to_capture ; 

__attribute__((used)) static int buffer_setup(struct videobuf_queue *q, unsigned int *count, unsigned int *size)
{
	int llength,lines;

	lines   = 16 * 2 ; /* 2 fields */
	llength = vbi_pixel_to_capture;

	*size = lines * llength;
	*count = 2;

	DEB_VBI(("count:%d, size:%d\n",*count,*size));

	return 0;
}