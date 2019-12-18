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
struct mousedev {scalar_t__ minor; int /*<<< orphan*/  mutex; int /*<<< orphan*/  open; int /*<<< orphan*/  handle; int /*<<< orphan*/  exist; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ MOUSEDEV_MIX ; 
 int input_open_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mixdev_open_devices () ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mousedev_open_device(struct mousedev *mousedev)
{
	int retval;

	retval = mutex_lock_interruptible(&mousedev->mutex);
	if (retval)
		return retval;

	if (mousedev->minor == MOUSEDEV_MIX)
		mixdev_open_devices();
	else if (!mousedev->exist)
		retval = -ENODEV;
	else if (!mousedev->open++) {
		retval = input_open_device(&mousedev->handle);
		if (retval)
			mousedev->open--;
	}

	mutex_unlock(&mousedev->mutex);
	return retval;
}