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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  lt_spinvolatile ; 

__attribute__((used)) static void
lt_spin_a_little_bit() 
{
	uint32_t i;
	
	for (i = 0; i < 10000; i++) {
		lt_spinvolatile++;
	}
}