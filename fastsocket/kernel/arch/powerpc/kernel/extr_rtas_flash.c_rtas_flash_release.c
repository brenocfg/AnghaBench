#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtas_update_flash_t {scalar_t__ status; int /*<<< orphan*/ * flist; } ;
struct proc_dir_entry {int /*<<< orphan*/  count; scalar_t__ data; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 scalar_t__ FLASH_AUTH ; 
 scalar_t__ FLASH_IMG_READY ; 
 struct proc_dir_entry* PDE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ flash_list_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_flash_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rtas_firmware_flash_list ; 

__attribute__((used)) static int rtas_flash_release(struct inode *inode, struct file *file)
{
	struct proc_dir_entry *dp = PDE(file->f_path.dentry->d_inode);
	struct rtas_update_flash_t *uf;
	
	uf = (struct rtas_update_flash_t *) dp->data;
	if (uf->flist) {    
		/* File was opened in write mode for a new flash attempt */
		/* Clear saved list */
		if (rtas_firmware_flash_list) {
			free_flash_list(rtas_firmware_flash_list);
			rtas_firmware_flash_list = NULL;
		}

		if (uf->status != FLASH_AUTH)  
			uf->status = flash_list_valid(uf->flist);

		if (uf->status == FLASH_IMG_READY) 
			rtas_firmware_flash_list = uf->flist;
		else
			free_flash_list(uf->flist);

		uf->flist = NULL;
	}

	atomic_dec(&dp->count);
	return 0;
}