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
struct pci_dev {int dummy; } ;
struct e752x_pvt {struct pci_dev* dev_d0f1; } ;
struct TYPE_2__ {char* x86_model_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  E752X_SYSBUS_ERRMASK ; 
 int /*<<< orphan*/  KERN_INFO ; 
 TYPE_1__ cpu_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e752x_printk (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strstr (char*,char*) ; 
 int sysbus_parity ; 

__attribute__((used)) static void e752x_init_sysbus_parity_mask(struct e752x_pvt *pvt)
{
	char *cpu_id = cpu_data(0).x86_model_id;
	struct pci_dev *dev = pvt->dev_d0f1;
	int enable = 1;

	/* Allow module parameter override, else see if CPU supports parity */
	if (sysbus_parity != -1) {
		enable = sysbus_parity;
	} else if (cpu_id[0] &&
		   ((strstr(cpu_id, "Pentium") && strstr(cpu_id, " M ")) ||
		    (strstr(cpu_id, "Celeron") && strstr(cpu_id, " M ")) ||
		    (strstr(cpu_id, "Core") && strstr(cpu_id, "Duo")))) {
		e752x_printk(KERN_INFO, "System Bus Parity not "
			     "supported by CPU, disabling\n");
		enable = 0;
	}

	if (enable)
		pci_write_config_word(dev, E752X_SYSBUS_ERRMASK, 0x0000);
	else
		pci_write_config_word(dev, E752X_SYSBUS_ERRMASK, 0x0309);
}