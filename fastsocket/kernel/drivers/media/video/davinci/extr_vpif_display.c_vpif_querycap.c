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
struct vpif_display_config {char* card_name; } ;
struct v4l2_capability {int capabilities; int /*<<< orphan*/  card; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; int /*<<< orphan*/  version; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct vpif_display_config* platform_data; } ;

/* Variables and functions */
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  VPIF_DISPLAY_VERSION_CODE ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* vpif_dev ; 

__attribute__((used)) static int vpif_querycap(struct file *file, void  *priv,
				struct v4l2_capability *cap)
{
	struct vpif_display_config *config = vpif_dev->platform_data;

	cap->version = VPIF_DISPLAY_VERSION_CODE;
	cap->capabilities = V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_STREAMING;
	strlcpy(cap->driver, "vpif display", sizeof(cap->driver));
	strlcpy(cap->bus_info, "Platform", sizeof(cap->bus_info));
	strlcpy(cap->card, config->card_name, sizeof(cap->card));

	return 0;
}