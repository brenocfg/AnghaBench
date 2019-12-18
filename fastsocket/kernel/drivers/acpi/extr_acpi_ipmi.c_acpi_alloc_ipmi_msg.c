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
struct pnp_dev {int /*<<< orphan*/  dev; } ;
struct acpi_ipmi_msg {struct acpi_ipmi_device* device; int /*<<< orphan*/  head; int /*<<< orphan*/  tx_complete; } ;
struct acpi_ipmi_device {struct pnp_dev* pnp_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct acpi_ipmi_msg* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct acpi_ipmi_msg *acpi_alloc_ipmi_msg(struct acpi_ipmi_device *ipmi)
{
	struct acpi_ipmi_msg *ipmi_msg;
	struct pnp_dev *pnp_dev = ipmi->pnp_dev;

	ipmi_msg = kzalloc(sizeof(struct acpi_ipmi_msg), GFP_KERNEL);
	if (!ipmi_msg)	{
		dev_warn(&pnp_dev->dev, "Can't allocate memory for ipmi_msg\n");
		return NULL;
	}
	init_completion(&ipmi_msg->tx_complete);
	INIT_LIST_HEAD(&ipmi_msg->head);
	ipmi_msg->device = ipmi;
	return ipmi_msg;
}