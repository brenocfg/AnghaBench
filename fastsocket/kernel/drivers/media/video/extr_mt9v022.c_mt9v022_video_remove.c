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
struct soc_camera_link {int /*<<< orphan*/  (* free_bus ) (struct soc_camera_link*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {int /*<<< orphan*/  vdev; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct soc_camera_link*) ; 
 struct soc_camera_link* to_soc_camera_link (struct soc_camera_device*) ; 

__attribute__((used)) static void mt9v022_video_remove(struct soc_camera_device *icd)
{
	struct soc_camera_link *icl = to_soc_camera_link(icd);

	dev_dbg(&icd->dev, "Video removed: %p, %p\n",
		icd->dev.parent, icd->vdev);
	if (icl->free_bus)
		icl->free_bus(icl);
}