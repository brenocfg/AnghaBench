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
 int DDC_SCL_IN ; 
 scalar_t__ REG ; 
 scalar_t__ ioaddr ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int bit_vooddc_getscl(void *data)
{
	return (0 != (readl(ioaddr + REG) & DDC_SCL_IN));
}