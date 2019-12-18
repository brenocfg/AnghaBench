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
struct TYPE_2__ {unsigned char* addr; int sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpm_serial_tstc () ; 
 int /*<<< orphan*/  eieio () ; 
 TYPE_1__* rbdf ; 
 int /*<<< orphan*/  sync () ; 

__attribute__((used)) static unsigned char cpm_serial_getc(void)
{
	unsigned char c;

	while (!cpm_serial_tstc())
		;

	sync();
	c = rbdf->addr[0];
	eieio();
	rbdf->sc |= 0x8000;

	return c;
}