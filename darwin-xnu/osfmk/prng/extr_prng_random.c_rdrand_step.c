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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */

__attribute__((used)) static int
rdrand_step(uint64_t * rand)
{
	uint8_t ok;

	asm volatile("rdrand %0; setc %1" : "=r"(*rand), "=qm"(ok));

	return (int)ok;
}