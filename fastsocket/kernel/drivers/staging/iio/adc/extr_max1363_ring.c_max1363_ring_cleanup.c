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
struct iio_dev {int /*<<< orphan*/  ring; int /*<<< orphan*/  pollfunc; scalar_t__ trig; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_put_trigger (scalar_t__) ; 
 int /*<<< orphan*/  iio_sw_rb_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_dettach_poll_func (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void max1363_ring_cleanup(struct iio_dev *indio_dev)
{
	/* ensure that the trigger has been detached */
	if (indio_dev->trig) {
		iio_put_trigger(indio_dev->trig);
		iio_trigger_dettach_poll_func(indio_dev->trig,
					      indio_dev->pollfunc);
	}
	kfree(indio_dev->pollfunc);
	iio_sw_rb_free(indio_dev->ring);
}