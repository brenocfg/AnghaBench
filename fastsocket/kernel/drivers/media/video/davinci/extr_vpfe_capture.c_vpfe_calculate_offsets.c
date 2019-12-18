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
struct vpfe_device {int field_off; int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_rect {int height; int width; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_image_window ) (struct v4l2_rect*) ;} ;
struct TYPE_4__ {TYPE_1__ hw_ops; } ;

/* Variables and functions */
 TYPE_2__* ccdc_dev ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  stub1 (struct v4l2_rect*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void vpfe_calculate_offsets(struct vpfe_device *vpfe_dev)
{
	struct v4l2_rect image_win;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_calculate_offsets\n");

	ccdc_dev->hw_ops.get_image_window(&image_win);
	vpfe_dev->field_off = image_win.height * image_win.width;
}