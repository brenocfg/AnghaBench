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
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static inline int CR_RL(unsigned int retry_limit)
{
	int value = 0;

	while (retry_limit) {
		retry_limit >>= 1;
		value++;
	}
	if (value > 0x7)
		printk("comedi: bug! retry_limit too large\n");
	return (value & 0x7) << 21;
}