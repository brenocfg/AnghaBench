#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct TYPE_3__ {int save; int /*<<< orphan*/  ctrl; } ;
struct TYPE_4__ {int save; int /*<<< orphan*/  ctrl; } ;
struct lpc_ich_priv {TYPE_1__ gpio; TYPE_2__ acpi; } ;

/* Variables and functions */
 struct lpc_ich_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpc_ich_restore_config_space(struct pci_dev *dev)
{
	struct lpc_ich_priv *priv = pci_get_drvdata(dev);

	if (priv->acpi.save >= 0) {
		pci_write_config_byte(dev, priv->acpi.ctrl, priv->acpi.save);
		priv->acpi.save = -1;
	}

	if (priv->gpio.save >= 0) {
		pci_write_config_byte(dev, priv->gpio.ctrl, priv->gpio.save);
		priv->gpio.save = -1;
	}
}