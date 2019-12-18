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
struct input_dev {int /*<<< orphan*/  dev; } ;
struct dc_mouse {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAPLE_FUNC_MOUSE ; 
 int /*<<< orphan*/  dc_mouse_callback ; 
 struct dc_mouse* maple_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maple_getcond_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_maple_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dc_mouse_close(struct input_dev *dev)
{
	struct dc_mouse *mse = maple_get_drvdata(to_maple_dev(&dev->dev));

	maple_getcond_callback(mse->mdev, dc_mouse_callback, 0,
		MAPLE_FUNC_MOUSE);
}