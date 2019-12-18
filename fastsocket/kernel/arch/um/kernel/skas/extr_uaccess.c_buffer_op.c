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

/* Variables and functions */
 scalar_t__ PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 int do_op_one_page (unsigned long,int,int,int (*) (unsigned long,int,void*),void*) ; 
 int min (scalar_t__,unsigned long) ; 

__attribute__((used)) static int buffer_op(unsigned long addr, int len, int is_write,
		     int (*op)(unsigned long, int, void *), void *arg)
{
	int size, remain, n;

	size = min(PAGE_ALIGN(addr) - addr, (unsigned long) len);
	remain = len;

	n = do_op_one_page(addr, size, is_write, op, arg);
	if (n != 0) {
		remain = (n < 0 ? remain : 0);
		goto out;
	}

	addr += size;
	remain -= size;
	if (remain == 0)
		goto out;

	while (addr < ((addr + remain) & PAGE_MASK)) {
		n = do_op_one_page(addr, PAGE_SIZE, is_write, op, arg);
		if (n != 0) {
			remain = (n < 0 ? remain : 0);
			goto out;
		}

		addr += PAGE_SIZE;
		remain -= PAGE_SIZE;
	}
	if (remain == 0)
		goto out;

	n = do_op_one_page(addr, remain, is_write, op, arg);
	if (n != 0) {
		remain = (n < 0 ? remain : 0);
		goto out;
	}

	return 0;
 out:
	return remain;
}