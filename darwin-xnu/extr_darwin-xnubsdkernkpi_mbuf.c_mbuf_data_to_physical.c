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
typedef  int /*<<< orphan*/  addr64_t ;

/* Variables and functions */
 scalar_t__ mcl_to_paddr (void*) ; 

addr64_t
mbuf_data_to_physical(void *ptr)
{
	return ((addr64_t)mcl_to_paddr(ptr));
}