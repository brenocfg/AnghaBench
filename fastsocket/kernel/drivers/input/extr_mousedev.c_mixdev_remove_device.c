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
struct mousedev {int /*<<< orphan*/  dev; int /*<<< orphan*/  mixdev_node; scalar_t__ mixdev_open; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mousedev_close_device (struct mousedev*) ; 
 TYPE_1__* mousedev_mix ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mixdev_remove_device(struct mousedev *mousedev)
{
	mutex_lock(&mousedev_mix->mutex);

	if (mousedev->mixdev_open) {
		mousedev->mixdev_open = 0;
		mousedev_close_device(mousedev);
	}

	list_del_init(&mousedev->mixdev_node);
	mutex_unlock(&mousedev_mix->mutex);

	put_device(&mousedev->dev);
}