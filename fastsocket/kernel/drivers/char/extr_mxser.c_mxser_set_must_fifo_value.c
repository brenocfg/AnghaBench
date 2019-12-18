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
typedef  int /*<<< orphan*/  u8 ;
struct mxser_port {scalar_t__ ioaddr; scalar_t__ rx_low_water; scalar_t__ rx_trigger; scalar_t__ rx_high_water; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOXA_MUST_EFR_BANK1 ; 
 int /*<<< orphan*/  MOXA_MUST_EFR_BANK_MASK ; 
 scalar_t__ MOXA_MUST_EFR_REGISTER ; 
 int /*<<< orphan*/  MOXA_MUST_ENTER_ENCHANCE ; 
 scalar_t__ MOXA_MUST_RBRTH_REGISTER ; 
 scalar_t__ MOXA_MUST_RBRTI_REGISTER ; 
 scalar_t__ MOXA_MUST_RBRTL_REGISTER ; 
 scalar_t__ UART_LCR ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxser_set_must_fifo_value(struct mxser_port *info)
{
	u8 oldlcr;
	u8 efr;

	oldlcr = inb(info->ioaddr + UART_LCR);
	outb(MOXA_MUST_ENTER_ENCHANCE, info->ioaddr + UART_LCR);

	efr = inb(info->ioaddr + MOXA_MUST_EFR_REGISTER);
	efr &= ~MOXA_MUST_EFR_BANK_MASK;
	efr |= MOXA_MUST_EFR_BANK1;

	outb(efr, info->ioaddr + MOXA_MUST_EFR_REGISTER);
	outb((u8)info->rx_high_water, info->ioaddr + MOXA_MUST_RBRTH_REGISTER);
	outb((u8)info->rx_trigger, info->ioaddr + MOXA_MUST_RBRTI_REGISTER);
	outb((u8)info->rx_low_water, info->ioaddr + MOXA_MUST_RBRTL_REGISTER);
	outb(oldlcr, info->ioaddr + UART_LCR);
}