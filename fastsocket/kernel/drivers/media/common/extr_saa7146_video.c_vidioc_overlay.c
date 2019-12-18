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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int saa7146_start_preview (void*) ; 
 int saa7146_stop_preview (void*) ; 

__attribute__((used)) static int vidioc_overlay(struct file *file, void *fh, unsigned int on)
{
	int err;

	DEB_D(("VIDIOC_OVERLAY on:%d\n", on));
	if (on)
		err = saa7146_start_preview(fh);
	else
		err = saa7146_stop_preview(fh);
	return err;
}