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
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {size_t model; int /*<<< orphan*/  udev; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX231XX_VERSION_CODE ; 
 int /*<<< orphan*/  V4L2_CAP_TUNER ; 
 TYPE_1__* cx231xx_boards ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int radio_querycap(struct file *file, void *priv,
			  struct v4l2_capability *cap)
{
	struct cx231xx *dev = ((struct cx231xx_fh *)priv)->dev;

	strlcpy(cap->driver, "cx231xx", sizeof(cap->driver));
	strlcpy(cap->card, cx231xx_boards[dev->model].name, sizeof(cap->card));
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));

	cap->version = CX231XX_VERSION_CODE;
	cap->capabilities = V4L2_CAP_TUNER;
	return 0;
}