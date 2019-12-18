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
struct v4l2_capability {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct cx88_core {TYPE_1__ board; } ;
struct cx8800_fh {struct cx8800_dev* dev; } ;
struct cx8800_dev {int /*<<< orphan*/  pci; struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX88_VERSION_CODE ; 
 int /*<<< orphan*/  V4L2_CAP_TUNER ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int radio_querycap (struct file *file, void  *priv,
					struct v4l2_capability *cap)
{
	struct cx8800_dev *dev  = ((struct cx8800_fh *)priv)->dev;
	struct cx88_core  *core = dev->core;

	strcpy(cap->driver, "cx8800");
	strlcpy(cap->card, core->board.name, sizeof(cap->card));
	sprintf(cap->bus_info,"PCI:%s", pci_name(dev->pci));
	cap->version = CX88_VERSION_CODE;
	cap->capabilities = V4L2_CAP_TUNER;
	return 0;
}