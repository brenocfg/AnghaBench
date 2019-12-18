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
typedef  int u8 ;

/* Variables and functions */
 int SCLP_CMDW_CONFIGURE_CPU ; 
 int do_cpu_configure (int) ; 

int sclp_cpu_configure(u8 cpu)
{
	return do_cpu_configure(SCLP_CMDW_CONFIGURE_CPU | cpu << 8);
}