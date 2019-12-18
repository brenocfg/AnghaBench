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
 scalar_t__ sparc_cpu_model ; 
 scalar_t__ sun4d ; 

__attribute__((used)) static char *cpu_mid_prop(void)
{
	if (sparc_cpu_model == sun4d)
		return "cpu-id";
	return "mid";
}