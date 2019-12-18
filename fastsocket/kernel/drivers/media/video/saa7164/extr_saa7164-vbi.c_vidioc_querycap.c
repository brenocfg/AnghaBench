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
struct v4l2_capability {int capabilities; scalar_t__ version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct saa7164_vbi_fh {struct saa7164_port* port; } ;
struct saa7164_port {struct saa7164_dev* dev; } ;
struct saa7164_dev {size_t board; int /*<<< orphan*/  pci; int /*<<< orphan*/  name; } ;
struct file {struct saa7164_vbi_fh* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* saa7164_boards ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
	struct v4l2_capability *cap)
{
	struct saa7164_vbi_fh *fh = file->private_data;
	struct saa7164_port *port = fh->port;
	struct saa7164_dev *dev = port->dev;

	strcpy(cap->driver, dev->name);
	strlcpy(cap->card, saa7164_boards[dev->board].name,
		sizeof(cap->card));
	sprintf(cap->bus_info, "PCI:%s", pci_name(dev->pci));

	cap->capabilities =
		V4L2_CAP_VBI_CAPTURE |
		V4L2_CAP_READWRITE     |
		0;

	cap->capabilities |= V4L2_CAP_TUNER;
	cap->version = 0;

	return 0;
}