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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int write_config_byte (struct pci_bus*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int write_config_dword (struct pci_bus*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int write_config_word (struct pci_bus*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_write(struct pci_bus *bus, unsigned int devfn, int where, int size, u32 val)
{
	switch (size) {
	case 1:
		return write_config_byte(bus, devfn, where, (u8) val);
	case 2:
		return write_config_word(bus, devfn, where, (u16) val);
	default:
		return write_config_dword(bus, devfn, where, val);
	}
}