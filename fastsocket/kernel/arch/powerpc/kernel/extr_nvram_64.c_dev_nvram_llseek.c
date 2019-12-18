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
struct file {scalar_t__ f_pos; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int (* nvram_size ) () ;} ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENODEV ; 
 TYPE_1__ ppc_md ; 
 int stub1 () ; 

__attribute__((used)) static loff_t dev_nvram_llseek(struct file *file, loff_t offset, int origin)
{
	int size;

	if (ppc_md.nvram_size == NULL)
		return -ENODEV;
	size = ppc_md.nvram_size();

	switch (origin) {
	case 1:
		offset += file->f_pos;
		break;
	case 2:
		offset += size;
		break;
	}
	if (offset < 0)
		return -EINVAL;
	file->f_pos = offset;
	return file->f_pos;
}