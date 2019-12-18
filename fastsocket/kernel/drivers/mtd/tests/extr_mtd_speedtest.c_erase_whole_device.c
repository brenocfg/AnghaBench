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
 scalar_t__* bbt ; 
 int /*<<< orphan*/  cond_resched () ; 
 unsigned int ebcnt ; 
 int erase_eraseblock (unsigned int) ; 

__attribute__((used)) static int erase_whole_device(void)
{
	int err;
	unsigned int i;

	for (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		err = erase_eraseblock(i);
		if (err)
			return err;
		cond_resched();
	}
	return 0;
}