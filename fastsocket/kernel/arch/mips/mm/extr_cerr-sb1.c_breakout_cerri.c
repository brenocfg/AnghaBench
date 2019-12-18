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
 unsigned int CP0_CERRI_DATA_PARITY ; 
 unsigned int CP0_CERRI_EXTERNAL ; 
 unsigned int CP0_CERRI_TAG_PARITY ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static inline void breakout_cerri(unsigned int val)
{
	if (val & CP0_CERRI_TAG_PARITY)
		printk(" tag-parity");
	if (val & CP0_CERRI_DATA_PARITY)
		printk(" data-parity");
	if (val & CP0_CERRI_EXTERNAL)
		printk(" external");
	printk("\n");
}