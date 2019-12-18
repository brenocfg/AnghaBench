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
struct osd_uld_device {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct osd_uld_device* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_DEBUG (char*,struct osd_uld_device*) ; 
 int /*<<< orphan*/  __uld_put (struct osd_uld_device*) ; 

__attribute__((used)) static int osd_uld_release(struct inode *inode, struct file *file)
{
	struct osd_uld_device *oud = file->private_data;

	OSD_DEBUG("osd_uld_release %p\n", file->private_data);
	file->private_data = NULL;
	__uld_put(oud);
	return 0;
}