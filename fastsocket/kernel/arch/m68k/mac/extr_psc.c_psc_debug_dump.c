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
 scalar_t__ pIERbase ; 
 scalar_t__ pIFRbase ; 
 int /*<<< orphan*/  printk (char*,int,int,int) ; 
 int /*<<< orphan*/  psc_present ; 
 scalar_t__ psc_read_byte (scalar_t__) ; 

__attribute__((used)) static void psc_debug_dump(void)
{
	int	i;

	if (!psc_present) return;
	for (i = 0x30 ; i < 0x70 ; i += 0x10) {
		printk("PSC #%d:  IFR = 0x%02X IER = 0x%02X\n",
			i >> 4,
			(int) psc_read_byte(pIFRbase + i),
			(int) psc_read_byte(pIERbase + i));
	}
}