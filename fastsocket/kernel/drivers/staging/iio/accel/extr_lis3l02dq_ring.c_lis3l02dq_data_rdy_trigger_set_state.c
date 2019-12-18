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
typedef  int /*<<< orphan*/  u8 ;
struct lis3l02dq_state {TYPE_1__* indio_dev; } ;
struct iio_trigger {struct lis3l02dq_state* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIS3L02DQ_REG_WAKE_UP_SRC_ADDR ; 
 int /*<<< orphan*/  __lis3l02dq_write_data_ready_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  iio_event_data_rdy_trig ; 
 int lis3l02dq_read_all (struct lis3l02dq_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lis3l02dq_spi_read_reg_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lis3l02dq_data_rdy_trigger_set_state(struct iio_trigger *trig,
						bool state)
{
	struct lis3l02dq_state *st = trig->private_data;
	int ret = 0;
	u8 t;
	__lis3l02dq_write_data_ready_config(&st->indio_dev->dev,
					    &iio_event_data_rdy_trig,
					    state);
	if (state == false) {
		/* possible quirk with handler currently worked around
		   by ensuring the work queue is empty */
		flush_scheduled_work();
		/* Clear any outstanding ready events */
		ret = lis3l02dq_read_all(st, NULL);
	}
	lis3l02dq_spi_read_reg_8(&st->indio_dev->dev,
				 LIS3L02DQ_REG_WAKE_UP_SRC_ADDR,
				 &t);
	return ret;
}