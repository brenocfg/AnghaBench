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
struct pidff_device {int /*<<< orphan*/ * pid_id; } ;
struct input_dev {TYPE_1__* ff; } ;
struct TYPE_2__ {struct pidff_device* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  pidff_playback_pid (struct pidff_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pidff_playback(struct input_dev *dev, int effect_id, int value)
{
	struct pidff_device *pidff = dev->ff->private;

	pidff_playback_pid(pidff, pidff->pid_id[effect_id], value);

	return 0;
}