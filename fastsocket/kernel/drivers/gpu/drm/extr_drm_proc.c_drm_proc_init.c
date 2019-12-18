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
struct proc_dir_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct drm_minor {int /*<<< orphan*/ * proc_root; TYPE_1__ proc_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_PROC_ENTRIES ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int drm_proc_create_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct drm_minor*) ; 
 int /*<<< orphan*/  drm_proc_list ; 
 int /*<<< orphan*/ * proc_mkdir (char*,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  remove_proc_entry (char*,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int drm_proc_init(struct drm_minor *minor, int minor_id,
		  struct proc_dir_entry *root)
{
	char name[64];
	int ret;

	INIT_LIST_HEAD(&minor->proc_nodes.list);
	sprintf(name, "%d", minor_id);
	minor->proc_root = proc_mkdir(name, root);
	if (!minor->proc_root) {
		DRM_ERROR("Cannot create /proc/dri/%s\n", name);
		return -1;
	}

	ret = drm_proc_create_files(drm_proc_list, DRM_PROC_ENTRIES,
				    minor->proc_root, minor);
	if (ret) {
		remove_proc_entry(name, root);
		minor->proc_root = NULL;
		DRM_ERROR("Failed to create core drm proc files\n");
		return ret;
	}

	return 0;
}