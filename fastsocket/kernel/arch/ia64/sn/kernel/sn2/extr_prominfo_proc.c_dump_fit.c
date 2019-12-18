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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dump_fit_entry (char*,unsigned long*) ; 
 scalar_t__ get_fit_entry (unsigned long,int,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_fit(char *page, unsigned long nasid)
{
	unsigned long fentry[2];
	int index;
	char *p;

	p = page;
	for (index=0;;index++) {
		BUG_ON(index * 60 > PAGE_SIZE);
		if (get_fit_entry(nasid, index, fentry, NULL, 0))
			break;
		p += dump_fit_entry(p, fentry);
	}

	return p - page;
}