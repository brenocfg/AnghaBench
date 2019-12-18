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
struct TYPE_2__ {int sc; unsigned char* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  eieio () ; 
 int /*<<< orphan*/  sync () ; 
 TYPE_1__* tbdf ; 

__attribute__((used)) static void cpm_serial_putc(unsigned char c)
{
	while (tbdf->sc & 0x8000)
		barrier();

	sync();

	tbdf->addr[0] = c;
	eieio();
	tbdf->sc |= 0x8000;
}