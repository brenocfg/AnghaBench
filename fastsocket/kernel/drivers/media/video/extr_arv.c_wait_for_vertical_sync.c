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
 int /*<<< orphan*/  ARVHCOUNT ; 
 int ar_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 

__attribute__((used)) static inline void wait_for_vertical_sync(int exp_line)
{
#if CHECK_LOST
	int tmout = 10000;	/* FIXME */
	int l;

	/*
	 * check HCOUNT because we cannot check vertical sync.
	 */
	for (; tmout >= 0; tmout--) {
		l = ar_inl(ARVHCOUNT);
		if (l == exp_line)
			break;
	}
	if (tmout < 0)
		printk("arv: lost %d -> %d\n", exp_line, l);
#else
	while (ar_inl(ARVHCOUNT) != exp_line)
		cpu_relax();
#endif
}