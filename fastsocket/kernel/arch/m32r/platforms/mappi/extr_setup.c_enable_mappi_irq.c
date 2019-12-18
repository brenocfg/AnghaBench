#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long icucr; } ;

/* Variables and functions */
 unsigned long M32R_ICUCR_IEN ; 
 unsigned long M32R_ICUCR_ILEVEL6 ; 
 TYPE_1__* icu_data ; 
 unsigned long irq2port (unsigned int) ; 
 int /*<<< orphan*/  outl (unsigned long,unsigned long) ; 

__attribute__((used)) static void enable_mappi_irq(unsigned int irq)
{
	unsigned long port, data;

	port = irq2port(irq);
	data = icu_data[irq].icucr|M32R_ICUCR_IEN|M32R_ICUCR_ILEVEL6;
	outl(data, port);
}