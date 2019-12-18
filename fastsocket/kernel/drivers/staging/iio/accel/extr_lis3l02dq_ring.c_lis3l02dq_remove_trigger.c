#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lis3l02dq_state {TYPE_1__* trig; } ;
struct iio_dev {struct lis3l02dq_state* dev_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_free_trigger (TYPE_1__*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void lis3l02dq_remove_trigger(struct iio_dev *indio_dev)
{
	struct lis3l02dq_state *state = indio_dev->dev_data;

	iio_trigger_unregister(state->trig);
	kfree(state->trig->name);
	iio_free_trigger(state->trig);
}