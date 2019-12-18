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
struct zoran_fh {struct zoran* zr; } ;
struct zoran {int /*<<< orphan*/  pci_dev; } ;
struct v4l2_capability {int capabilities; int /*<<< orphan*/  version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; int /*<<< orphan*/  card; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_VERSION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR_VERSION ; 
 int /*<<< orphan*/  MINOR_VERSION ; 
 int /*<<< orphan*/  RELEASE_VERSION ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int V4L2_CAP_VIDEO_OVERLAY ; 
 char* ZR_DEVNAME (struct zoran*) ; 
 int /*<<< orphan*/  memset (struct v4l2_capability*,int /*<<< orphan*/ ,int) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int zoran_querycap(struct file *file, void *__fh, struct v4l2_capability *cap)
{
	struct zoran_fh *fh = __fh;
	struct zoran *zr = fh->zr;

	memset(cap, 0, sizeof(*cap));
	strncpy(cap->card, ZR_DEVNAME(zr), sizeof(cap->card)-1);
	strncpy(cap->driver, "zoran", sizeof(cap->driver)-1);
	snprintf(cap->bus_info, sizeof(cap->bus_info), "PCI:%s",
		 pci_name(zr->pci_dev));
	cap->version = KERNEL_VERSION(MAJOR_VERSION, MINOR_VERSION,
			   RELEASE_VERSION);
	cap->capabilities = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE |
			    V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_VIDEO_OVERLAY;
	return 0;
}