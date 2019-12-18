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
struct vfsmount {int dummy; } ;
struct file_system_type {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_KERNMOUNT ; 
 struct vfsmount* vfs_kern_mount (struct file_system_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

struct vfsmount *kern_mount_data(struct file_system_type *type, void *data)
{
	return vfs_kern_mount(type, MS_KERNMOUNT, type->name, data);
}