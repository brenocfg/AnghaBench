#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {TYPE_1__* private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer_len; scalar_t__ buffer; } ;
typedef  TYPE_1__ fnic_dbgfs_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  fnic_get_trace_data (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int trace_max_pages ; 
 scalar_t__ vmalloc (int) ; 

__attribute__((used)) static int fnic_trace_debugfs_open(struct inode *inode,
				  struct file *file)
{
	fnic_dbgfs_t *fnic_dbg_prt;
	fnic_dbg_prt = kzalloc(sizeof(fnic_dbgfs_t), GFP_KERNEL);
	if (!fnic_dbg_prt)
		return -ENOMEM;

	fnic_dbg_prt->buffer = vmalloc((3*(trace_max_pages * PAGE_SIZE)));
	if (!fnic_dbg_prt->buffer) {
		kfree(fnic_dbg_prt);
		return -ENOMEM;
	}
	memset((void *)fnic_dbg_prt->buffer, 0,
			  (3*(trace_max_pages * PAGE_SIZE)));
	fnic_dbg_prt->buffer_len = fnic_get_trace_data(fnic_dbg_prt);
	file->private_data = fnic_dbg_prt;
	return 0;
}