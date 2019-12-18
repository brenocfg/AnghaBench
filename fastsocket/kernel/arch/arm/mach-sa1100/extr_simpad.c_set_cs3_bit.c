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
typedef  int CS3BUSTYPE ;

/* Variables and functions */
 scalar_t__ CS3_BASE ; 
 int cs3_shadow ; 

void set_cs3_bit(int value)
{
	cs3_shadow |= value;
	*(CS3BUSTYPE *)(CS3_BASE) = cs3_shadow;
}