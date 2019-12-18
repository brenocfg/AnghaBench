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
 scalar_t__ SMSC_FDC37M81X_CONFIG_DATA ; 
 scalar_t__ SMSC_FDC37M81X_CONFIG_INDEX ; 
 scalar_t__ g_smsc_fdc37m81x_base ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static inline void smsc_dc37m81x_wr(unsigned char index, unsigned char data)
{
	outb(index, g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_INDEX);
	outb(data, g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_DATA);
}