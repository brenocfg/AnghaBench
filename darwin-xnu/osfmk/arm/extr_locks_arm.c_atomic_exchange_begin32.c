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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum memory_order { ____Placeholder_memory_order } memory_order ;

/* Variables and functions */
 int /*<<< orphan*/  load_exclusive32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint32_t
atomic_exchange_begin32(uint32_t *target, uint32_t *previous, enum memory_order ord)
{
	uint32_t	val;

	val = load_exclusive32(target, ord);
	*previous = val;
	return val;
}