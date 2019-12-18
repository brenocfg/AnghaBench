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
 int ebcnt ; 
 int simple_rand () ; 

__attribute__((used)) static int rand_eb(void)
{
	int eb;

again:
	if (ebcnt < 32768)
		eb = simple_rand();
	else
		eb = (simple_rand() << 15) | simple_rand();
	/* Read or write up 2 eraseblocks at a time - hence 'ebcnt - 1' */
	eb %= (ebcnt - 1);
	if (bbt[eb])
		goto again;
	return eb;
}