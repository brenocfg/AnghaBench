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
struct file {scalar_t__ f_pos; TYPE_1__* private_data; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ buffer_len; } ;
typedef  TYPE_1__ fnic_dbgfs_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 

__attribute__((used)) static loff_t fnic_trace_debugfs_lseek(struct file *file,
					loff_t offset,
					int howto)
{
	fnic_dbgfs_t *fnic_dbg_prt = file->private_data;
	loff_t pos = -1;

	switch (howto) {
	case 0:
		pos = offset;
		break;
	case 1:
		pos = file->f_pos + offset;
		break;
	case 2:
		pos = fnic_dbg_prt->buffer_len - offset;
	}
	return (pos < 0 || pos > fnic_dbg_prt->buffer_len) ?
			  -EINVAL : (file->f_pos = pos);
}