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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  outl (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 

void write_pci_config_byte(u8 bus, u8 slot, u8 func, u8 offset, u8 val)
{
	pr_debug("%x writing to %x: %x\n", slot, offset, val);
	outl(0x80000000 | (bus<<16) | (slot<<11) | (func<<8) | offset, 0xcf8);
	outb(val, 0xcfc + (offset&3));
}