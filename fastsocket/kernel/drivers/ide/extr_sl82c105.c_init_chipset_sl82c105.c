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
typedef  int u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int CTRL_P0EN ; 
 int CTRL_P0F16 ; 
 int CTRL_P1F16 ; 
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 

__attribute__((used)) static int init_chipset_sl82c105(struct pci_dev *dev)
{
	u32 val;

	DBG(("init_chipset_sl82c105()\n"));

	pci_read_config_dword(dev, 0x40, &val);
	val |= CTRL_P0EN | CTRL_P0F16 | CTRL_P1F16;
	pci_write_config_dword(dev, 0x40, val);

	return 0;
}