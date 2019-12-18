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
struct initio_host {int semaph; scalar_t__ addr; } ;

/* Variables and functions */
 int TSS_INT_PENDING ; 
 scalar_t__ TUL_Int ; 
 scalar_t__ TUL_Mask ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  tulip_main (struct initio_host*) ; 

__attribute__((used)) static int initio_isr(struct initio_host * host)
{
	if (inb(host->addr + TUL_Int) & TSS_INT_PENDING) {
		if (host->semaph == 1) {
			outb(0x1F, host->addr + TUL_Mask);
			/* Disable Tulip SCSI Int */
			host->semaph = 0;

			tulip_main(host);

			host->semaph = 1;
			outb(0x0F, host->addr + TUL_Mask);
			return 1;
		}
	}
	return 0;
}