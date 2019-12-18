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
struct page {int dummy; } ;
struct file {int dummy; } ;
struct address_space {TYPE_1__* host; } ;
typedef  unsigned int loff_t ;
typedef  int /*<<< orphan*/  get_block_t ;
struct TYPE_2__ {unsigned int i_size; } ;

/* Variables and functions */
 int nobh_write_begin_newtrunc (struct file*,struct address_space*,unsigned int,unsigned int,unsigned int,struct page**,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmtruncate (TYPE_1__*,unsigned int) ; 

int nobh_write_begin(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned flags,
			struct page **pagep, void **fsdata,
			get_block_t *get_block)
{
	int ret;

	ret = nobh_write_begin_newtrunc(file, mapping, pos, len, flags,
					pagep, fsdata, get_block);

	/*
	 * prepare_write() may have instantiated a few blocks
	 * outside i_size.  Trim these off again. Don't need
	 * i_size_read because we hold i_mutex.
	 */
	if (unlikely(ret)) {
		loff_t isize = mapping->host->i_size;
		if (pos + len > isize)
			vmtruncate(mapping->host, isize);
	}

	return ret;
}