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
struct v4l2_capability {int capabilities; int /*<<< orphan*/  version; scalar_t__ bus_info; scalar_t__ card; scalar_t__ driver; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {TYPE_2__* ext_vv_data; int /*<<< orphan*/  pci; TYPE_1__* ext; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int capabilities; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7146_VERSION_CODE ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int V4L2_CAP_VIDEO_OVERLAY ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void *fh, struct v4l2_capability *cap)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;

	strcpy((char *)cap->driver, "saa7146 v4l2");
	strlcpy((char *)cap->card, dev->ext->name, sizeof(cap->card));
	sprintf((char *)cap->bus_info, "PCI:%s", pci_name(dev->pci));
	cap->version = SAA7146_VERSION_CODE;
	cap->capabilities =
		V4L2_CAP_VIDEO_CAPTURE |
		V4L2_CAP_VIDEO_OVERLAY |
		V4L2_CAP_READWRITE |
		V4L2_CAP_STREAMING;
	cap->capabilities |= dev->ext_vv_data->capabilities;
	return 0;
}