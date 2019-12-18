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
struct sa1100_irda {unsigned int power; } ;

/* Variables and functions */
 int __sa1100_irda_set_power (struct sa1100_irda*,unsigned int) ; 

__attribute__((used)) static inline int
sa1100_set_power(struct sa1100_irda *si, unsigned int state)
{
	int ret;

	ret = __sa1100_irda_set_power(si, state);
	if (ret == 0)
		si->power = state;

	return ret;
}