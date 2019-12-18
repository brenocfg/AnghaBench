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
 int ST_address ; 
 int addr_A1 ; 
 scalar_t__ writebuff_ptr ; 

__attribute__((used)) static void internal_reset(void)
{
	writebuff_ptr = 0;
	ST_address = addr_A1 = -1;
}