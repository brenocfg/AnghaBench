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
 unsigned long KERNBASE ; 
 unsigned long kern_base ; 

__attribute__((used)) static unsigned long kimage_addr_to_ra(const char *p)
{
	unsigned long val = (unsigned long) p;

	return kern_base + (val - KERNBASE);
}