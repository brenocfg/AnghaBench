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
typedef  int /*<<< orphan*/  kern_allocation_name_t ;

/* Variables and functions */
 char const* KA_NAME (int /*<<< orphan*/ ) ; 

const char *
kern_allocation_get_name(kern_allocation_name_t allocation)
{
    return (KA_NAME(allocation));
}