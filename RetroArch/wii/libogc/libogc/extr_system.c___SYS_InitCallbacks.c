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
 int /*<<< orphan*/  __POWCallback ; 
 int /*<<< orphan*/  __POWDefaultHandler ; 
 int /*<<< orphan*/  __RSWCallback ; 
 int /*<<< orphan*/  __RSWDefaultHandler ; 
 scalar_t__ __sys_resetdown ; 

void __SYS_InitCallbacks()
{
#if defined(HW_RVL)
	__POWCallback = __POWDefaultHandler;
	__sys_resetdown = 0;
#endif
	__RSWCallback = __RSWDefaultHandler;
}