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
struct TYPE_2__ {struct dc_pad* platform_data; } ;
struct input_dev {TYPE_1__ dev; } ;
struct dc_pad {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MAPLE_FUNC_CONTROLLER ; 
 int /*<<< orphan*/  dc_pad_callback ; 
 int /*<<< orphan*/  maple_getcond_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dc_pad_open(struct input_dev *dev)
{
	struct dc_pad *pad = dev->dev.platform_data;

	maple_getcond_callback(pad->mdev, dc_pad_callback, HZ/20,
		MAPLE_FUNC_CONTROLLER);

	return 0;
}