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
struct v4l2_capability {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct TYPE_3__ {int /*<<< orphan*/  pci; } ;
struct bttv {TYPE_1__ c; TYPE_2__* radio_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTTV_VERSION_CODE ; 
 int /*<<< orphan*/  V4L2_CAP_TUNER ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int radio_querycap(struct file *file, void *priv,
					struct v4l2_capability *cap)
{
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;

	strcpy(cap->driver, "bttv");
	strlcpy(cap->card, btv->radio_dev->name, sizeof(cap->card));
	sprintf(cap->bus_info, "PCI:%s", pci_name(btv->c.pci));
	cap->version = BTTV_VERSION_CODE;
	cap->capabilities = V4L2_CAP_TUNER;

	return 0;
}