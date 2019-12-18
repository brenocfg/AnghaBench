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
struct gpio_event_info {int (* func ) (int /*<<< orphan*/ ,struct gpio_event_info*,int /*<<< orphan*/ *,int) ;} ;
struct gpio_event {int /*<<< orphan*/ * state; int /*<<< orphan*/  input_dev; TYPE_1__* info; } ;
struct TYPE_2__ {int info_count; struct gpio_event_info** info; } ;

/* Variables and functions */
 int ENODEV ; 
 int GPIO_EVENT_FUNC_INIT ; 
 int GPIO_EVENT_FUNC_RESUME ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (int /*<<< orphan*/ ,struct gpio_event_info*,int /*<<< orphan*/ *,int) ; 
 int stub2 (int /*<<< orphan*/ ,struct gpio_event_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int gpio_event_call_all_func(struct gpio_event *ip, int func)
{
	int i;
	int ret;
	struct gpio_event_info **ii;

	if (func == GPIO_EVENT_FUNC_INIT || func == GPIO_EVENT_FUNC_RESUME) {
		ii = ip->info->info;
		for (i = 0; i < ip->info->info_count; i++, ii++) {
			if ((*ii)->func == NULL) {
				ret = -ENODEV;
				pr_err("gpio_event_probe: Incomplete pdata, "
					"no function\n");
				goto err_no_func;
			}
			ret = (*ii)->func(ip->input_dev, *ii, &ip->state[i],
					  func);
			if (ret) {
				pr_err("gpio_event_probe: function failed\n");
				goto err_func_failed;
			}
		}
		return 0;
	}

	ret = 0;
	i = ip->info->info_count;
	ii = ip->info->info + i;
	while (i > 0) {
		i--;
		ii--;
		(*ii)->func(ip->input_dev, *ii, &ip->state[i], func & ~1);
err_func_failed:
err_no_func:
		;
	}
	return ret;
}