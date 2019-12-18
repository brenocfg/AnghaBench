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
struct video_device {int dummy; } ;
struct saa7146_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

int saa7146_unregister_device(struct video_device **vid, struct saa7146_dev* dev)
{
	DEB_EE(("dev:%p\n",dev));

	video_unregister_device(*vid);
	*vid = NULL;

	return 0;
}