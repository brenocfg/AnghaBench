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
 void** gpio_pa_owners ; 
 void** gpio_pb_owners ; 
 void** gpio_pg_owners ; 
 void* if_unclaimed ; 

__attribute__((used)) static int cris_io_interface_init(void)
{
	static int first = 1;
	int i;

	if (!first) {
		return 0;
	}
	first = 0;

	for (i = 0; i<8; i++) {
		gpio_pa_owners[i] = if_unclaimed;
		gpio_pb_owners[i] = if_unclaimed;
		gpio_pg_owners[i] = if_unclaimed;
	}
	for (; i<32; i++) {
		gpio_pg_owners[i] = if_unclaimed;
	}
	return 0;
}