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
typedef  int /*<<< orphan*/  u16 ;
struct pidff_device {int dummy; } ;
struct input_dev {TYPE_1__* ff; } ;
struct TYPE_2__ {struct pidff_device* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  pidff_autocenter (struct pidff_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pidff_set_autocenter(struct input_dev *dev, u16 magnitude)
{
	struct pidff_device *pidff = dev->ff->private;

	pidff_autocenter(pidff, magnitude);
}