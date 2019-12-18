#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct max1363_state {int /*<<< orphan*/  poll_work; TYPE_2__* indio_dev; } ;
struct iio_dev {TYPE_4__* ring; int /*<<< orphan*/  modes; TYPE_3__* pollfunc; struct max1363_state* dev_data; } ;
struct TYPE_9__ {int /*<<< orphan*/ * predisable; int /*<<< orphan*/ * preenable; int /*<<< orphan*/ * postenable; } ;
struct TYPE_8__ {struct iio_dev* private_data; int /*<<< orphan*/ * poll_func_main; } ;
struct TYPE_7__ {TYPE_1__* ring; } ;
struct TYPE_6__ {int /*<<< orphan*/  access; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INDIO_RING_TRIGGERED ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_ring_sw_register_funcs (int /*<<< orphan*/ *) ; 
 TYPE_4__* iio_sw_rb_allocate (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_sw_rb_free (TYPE_4__*) ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max1363_poll_bh_to_ring ; 
 int /*<<< orphan*/  max1363_poll_func_th ; 
 int /*<<< orphan*/  max1363_ring_postenable ; 
 int /*<<< orphan*/  max1363_ring_predisable ; 
 int /*<<< orphan*/  max1363_ring_preenable ; 

int max1363_register_ring_funcs_and_init(struct iio_dev *indio_dev)
{
	struct max1363_state *st = indio_dev->dev_data;
	int ret = 0;

	indio_dev->ring = iio_sw_rb_allocate(indio_dev);
	if (!indio_dev->ring) {
		ret = -ENOMEM;
		goto error_ret;
	}
	/* Effectively select the ring buffer implementation */
	iio_ring_sw_register_funcs(&st->indio_dev->ring->access);
	indio_dev->pollfunc = kzalloc(sizeof(*indio_dev->pollfunc), GFP_KERNEL);
	if (indio_dev->pollfunc == NULL) {
		ret = -ENOMEM;
		goto error_deallocate_sw_rb;
	}
	/* Configure the polling function called on trigger interrupts */
	indio_dev->pollfunc->poll_func_main = &max1363_poll_func_th;
	indio_dev->pollfunc->private_data = indio_dev;

	/* Ring buffer functions - here trigger setup related */
	indio_dev->ring->postenable = &max1363_ring_postenable;
	indio_dev->ring->preenable = &max1363_ring_preenable;
	indio_dev->ring->predisable = &max1363_ring_predisable;
	INIT_WORK(&st->poll_work, &max1363_poll_bh_to_ring);

	/* Flag that polled ring buffering is possible */
	indio_dev->modes |= INDIO_RING_TRIGGERED;
	return 0;
error_deallocate_sw_rb:
	iio_sw_rb_free(indio_dev->ring);
error_ret:
	return ret;
}