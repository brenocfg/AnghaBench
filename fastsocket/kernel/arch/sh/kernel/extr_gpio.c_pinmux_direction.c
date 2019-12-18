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
struct pinmux_info {TYPE_1__* gpios; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_CFG_DRYRUN ; 
 int /*<<< orphan*/  GPIO_CFG_FREE ; 
 int /*<<< orphan*/  GPIO_CFG_REQ ; 
 int PINMUX_FLAG_TYPE ; 
#define  PINMUX_TYPE_GPIO 132 
#define  PINMUX_TYPE_INPUT 131 
#define  PINMUX_TYPE_INPUT_PULLDOWN 130 
#define  PINMUX_TYPE_INPUT_PULLUP 129 
#define  PINMUX_TYPE_OUTPUT 128 
 scalar_t__ pinmux_config_gpio (struct pinmux_info*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pinmux_direction(struct pinmux_info *gpioc,
			    unsigned gpio, int new_pinmux_type)
{
	int pinmux_type;
	int ret = -EINVAL;

	if (!gpioc)
		goto err_out;

	pinmux_type = gpioc->gpios[gpio].flags & PINMUX_FLAG_TYPE;

	switch (pinmux_type) {
	case PINMUX_TYPE_GPIO:
		break;
	case PINMUX_TYPE_OUTPUT:
	case PINMUX_TYPE_INPUT:
	case PINMUX_TYPE_INPUT_PULLUP:
	case PINMUX_TYPE_INPUT_PULLDOWN:
		pinmux_config_gpio(gpioc, gpio, pinmux_type, GPIO_CFG_FREE);
		break;
	default:
		goto err_out;
	}

	if (pinmux_config_gpio(gpioc, gpio,
			       new_pinmux_type,
			       GPIO_CFG_DRYRUN) != 0)
		goto err_out;

	if (pinmux_config_gpio(gpioc, gpio,
			       new_pinmux_type,
			       GPIO_CFG_REQ) != 0)
		BUG();

	gpioc->gpios[gpio].flags &= ~PINMUX_FLAG_TYPE;
	gpioc->gpios[gpio].flags |= new_pinmux_type;

	ret = 0;
 err_out:
	return ret;
}