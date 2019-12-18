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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct aer_err_info {size_t severity; int /*<<< orphan*/  id; scalar_t__ multi_error_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/ * aer_error_severity_string ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void aer_print_port_info(struct pci_dev *dev, struct aer_err_info *info)
{
	dev_info(&dev->dev, "AER: %s%s error received: id=%04x\n",
		info->multi_error_valid ? "Multiple " : "",
		aer_error_severity_string[info->severity], info->id);
}