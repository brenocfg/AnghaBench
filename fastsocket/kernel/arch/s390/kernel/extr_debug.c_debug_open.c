#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_14__ {TYPE_2__* dentry; } ;
struct file {TYPE_5__* private_data; TYPE_3__ f_path; } ;
struct TYPE_16__ {scalar_t__ act_entry_offset; int /*<<< orphan*/  act_entry; scalar_t__ act_page; scalar_t__ act_area; TYPE_4__* view; TYPE_6__* debug_info_org; TYPE_6__* debug_info_snap; scalar_t__ offset; } ;
typedef  TYPE_5__ file_private_info_t ;
struct TYPE_17__ {TYPE_4__** views; TYPE_2__** debugfs_entries; } ;
typedef  TYPE_6__ debug_info_t ;
struct TYPE_15__ {int /*<<< orphan*/  header_proc; int /*<<< orphan*/  format_proc; } ;
struct TYPE_13__ {TYPE_1__* d_inode; } ;
struct TYPE_12__ {TYPE_6__* i_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_AREAS ; 
 int DEBUG_MAX_VIEWS ; 
 int /*<<< orphan*/  DEBUG_PROLOG_ENTRY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NO_AREAS ; 
 TYPE_6__* debug_info_copy (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_info_free (TYPE_6__*) ; 
 int /*<<< orphan*/  debug_info_get (TYPE_6__*) ; 
 int /*<<< orphan*/  debug_mutex ; 
 TYPE_5__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
debug_open(struct inode *inode, struct file *file)
{
	int i, rc = 0;
	file_private_info_t *p_info;
	debug_info_t *debug_info, *debug_info_snapshot;

	mutex_lock(&debug_mutex);
	debug_info = file->f_path.dentry->d_inode->i_private;
	/* find debug view */
	for (i = 0; i < DEBUG_MAX_VIEWS; i++) {
		if (!debug_info->views[i])
			continue;
		else if (debug_info->debugfs_entries[i] ==
			 file->f_path.dentry) {
			goto found;	/* found view ! */
		}
	}
	/* no entry found */
	rc = -EINVAL;
	goto out;

found:

	/* Make snapshot of current debug areas to get it consistent.     */
	/* To copy all the areas is only needed, if we have a view which  */
	/* formats the debug areas. */

	if(!debug_info->views[i]->format_proc &&
		!debug_info->views[i]->header_proc){
		debug_info_snapshot = debug_info_copy(debug_info, NO_AREAS);
	} else {
		debug_info_snapshot = debug_info_copy(debug_info, ALL_AREAS);
	}

	if(!debug_info_snapshot){
		rc = -ENOMEM;
		goto out;
	}
	p_info = kmalloc(sizeof(file_private_info_t),
						GFP_KERNEL);
	if(!p_info){
		debug_info_free(debug_info_snapshot);
		rc = -ENOMEM;
		goto out;
	}
	p_info->offset = 0;
	p_info->debug_info_snap = debug_info_snapshot;
	p_info->debug_info_org  = debug_info;
	p_info->view = debug_info->views[i];
	p_info->act_area = 0;
	p_info->act_page = 0;
	p_info->act_entry = DEBUG_PROLOG_ENTRY;
	p_info->act_entry_offset = 0;
	file->private_data = p_info;
	debug_info_get(debug_info);
out:
	mutex_unlock(&debug_mutex);
	return rc;
}