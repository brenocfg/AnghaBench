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
 unsigned long* lasat_int_mask ; 
 unsigned long* lasat_int_status ; 

__attribute__((used)) static unsigned long get_int_status_100(void)
{
	return *lasat_int_status & *lasat_int_mask;
}