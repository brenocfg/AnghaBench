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
struct input_dev {int dummy; } ;
struct cm109_dev {int buzzer_state; int /*<<< orphan*/  resetting; TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int EV_SND ; 
#define  SND_BELL 129 
#define  SND_TONE 128 
 int /*<<< orphan*/  cm109_toggle_buzzer_async (struct cm109_dev*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,int) ; 
 struct cm109_dev* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int cm109_input_ev(struct input_dev *idev, unsigned int type,
			  unsigned int code, int value)
{
	struct cm109_dev *dev = input_get_drvdata(idev);

	dev_dbg(&dev->udev->dev,
		"input_ev: type=%u code=%u value=%d\n", type, code, value);

	if (type != EV_SND)
		return -EINVAL;

	switch (code) {
	case SND_TONE:
	case SND_BELL:
		dev->buzzer_state = !!value;
		if (!dev->resetting)
			cm109_toggle_buzzer_async(dev);
		return 0;

	default:
		return -EINVAL;
	}
}