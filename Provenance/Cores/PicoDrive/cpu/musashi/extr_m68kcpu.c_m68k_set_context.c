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
 void* m68ki_cpu_p ; 

void m68k_set_context(void* src)
{
	// notaz
	if(src) m68ki_cpu_p = src;
//	if(src) m68ki_cpu = *(m68ki_cpu_core*)src;
}