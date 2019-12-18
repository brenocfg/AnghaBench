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
struct sht15_data {scalar_t__ flag; TYPE_1__* pdata; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  read_work; int /*<<< orphan*/  interrupt_handled; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio_data; } ;

/* Variables and functions */
 int ETIME ; 
 scalar_t__ SHT15_READING_NOTHING ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sht15_connection_reset (struct sht15_data*) ; 
 int sht15_send_cmd (struct sht15_data*,int) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sht15_update_single_val(struct sht15_data *data,
					  int command,
					  int timeout_msecs)
{
	int ret;
	ret = sht15_send_cmd(data, command);
	if (ret)
		return ret;

	gpio_direction_input(data->pdata->gpio_data);
	atomic_set(&data->interrupt_handled, 0);

	enable_irq(gpio_to_irq(data->pdata->gpio_data));
	if (gpio_get_value(data->pdata->gpio_data) == 0) {
		disable_irq_nosync(gpio_to_irq(data->pdata->gpio_data));
		/* Only relevant if the interrupt hasn't occured. */
		if (!atomic_read(&data->interrupt_handled))
			schedule_work(&data->read_work);
	}
	ret = wait_event_timeout(data->wait_queue,
				 (data->flag == SHT15_READING_NOTHING),
				 msecs_to_jiffies(timeout_msecs));
	if (ret == 0) {/* timeout occurred */
		disable_irq_nosync(gpio_to_irq(data->pdata->gpio_data));
		sht15_connection_reset(data);
		return -ETIME;
	}
	return 0;
}