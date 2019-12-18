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
struct file {TYPE_1__* f_op; } ;
typedef  unsigned long loff_t ;
struct TYPE_2__ {scalar_t__ (* llseek ) (struct file*,unsigned long,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ dump_interrupted () ; 
 int /*<<< orphan*/  dump_write (struct file*,char*,unsigned long) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 scalar_t__ no_llseek ; 
 scalar_t__ stub1 (struct file*,unsigned long,int /*<<< orphan*/ ) ; 

int dump_seek(struct file *file, loff_t off)
{
	int ret = 1;

	if (file->f_op->llseek && file->f_op->llseek != no_llseek) {
		if (dump_interrupted() ||
		    file->f_op->llseek(file, off, SEEK_CUR) < 0)
			return 0;
	} else {
		char *buf = (char *)get_zeroed_page(GFP_KERNEL);

		if (!buf)
			return 0;
		while (off > 0) {
			unsigned long n = off;

			if (n > PAGE_SIZE)
				n = PAGE_SIZE;
			if (!dump_write(file, buf, n)) {
				ret = 0;
				break;
			}
			off -= n;
		}
		free_page((unsigned long)buf);
	}
	return ret;
}