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
 size_t ASC_ENABLE ; 
 scalar_t__* mac_asc_regs ; 

__attribute__((used)) static void mac_nosound( unsigned long ignored )
{
	mac_asc_regs[ ASC_ENABLE ] = 0;
}