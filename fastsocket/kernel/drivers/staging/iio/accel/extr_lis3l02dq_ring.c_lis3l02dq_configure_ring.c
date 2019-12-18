#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lis3l02dq_state {int /*<<< orphan*/  work_trigger_to_ring; } ;
struct iio_ring_buffer {int /*<<< orphan*/  owner; int /*<<< orphan*/ * predisable; int /*<<< orphan*/ * postenable; int /*<<< orphan*/ * preenable; int /*<<< orphan*/  access; } ;
struct iio_dev {int scan_timestamp; struct iio_ring_buffer* ring; int /*<<< orphan*/  modes; TYPE_1__* pollfunc; int /*<<< orphan*/ * scan_el_attrs; struct lis3l02dq_state* dev_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  number; } ;
struct TYPE_7__ {int /*<<< orphan*/  number; } ;
struct TYPE_6__ {int /*<<< orphan*/  number; } ;
struct TYPE_5__ {struct iio_dev* private_data; int /*<<< orphan*/ * poll_func_main; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INDIO_RING_TRIGGERED ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  iio_ring_sw_register_funcs (int /*<<< orphan*/ *) ; 
 TYPE_4__ iio_scan_el_accel_x ; 
 TYPE_3__ iio_scan_el_accel_y ; 
 TYPE_2__ iio_scan_el_accel_z ; 
 int /*<<< orphan*/  iio_scan_mask_set (struct iio_dev*,int /*<<< orphan*/ ) ; 
 struct iio_ring_buffer* iio_sw_rb_allocate (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_sw_rb_free (struct iio_ring_buffer*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lis3l02dq_data_rdy_ring_postenable ; 
 int /*<<< orphan*/  lis3l02dq_data_rdy_ring_predisable ; 
 int /*<<< orphan*/  lis3l02dq_data_rdy_ring_preenable ; 
 int /*<<< orphan*/  lis3l02dq_poll_func_th ; 
 int /*<<< orphan*/  lis3l02dq_scan_el_group ; 
 int /*<<< orphan*/  lis3l02dq_trigger_bh_to_ring ; 

int lis3l02dq_configure_ring(struct iio_dev *indio_dev)
{
	int ret = 0;
	struct lis3l02dq_state *st = indio_dev->dev_data;
	struct iio_ring_buffer *ring;
	INIT_WORK(&st->work_trigger_to_ring, lis3l02dq_trigger_bh_to_ring);
	/* Set default scan mode */

	iio_scan_mask_set(indio_dev, iio_scan_el_accel_x.number);
	iio_scan_mask_set(indio_dev, iio_scan_el_accel_y.number);
	iio_scan_mask_set(indio_dev, iio_scan_el_accel_z.number);
	indio_dev->scan_timestamp = true;

	indio_dev->scan_el_attrs = &lis3l02dq_scan_el_group;

	ring = iio_sw_rb_allocate(indio_dev);
	if (!ring) {
		ret = -ENOMEM;
		return ret;
	}
	indio_dev->ring = ring;
	/* Effectively select the ring buffer implementation */
	iio_ring_sw_register_funcs(&ring->access);
	ring->preenable = &lis3l02dq_data_rdy_ring_preenable;
	ring->postenable = &lis3l02dq_data_rdy_ring_postenable;
	ring->predisable = &lis3l02dq_data_rdy_ring_predisable;
	ring->owner = THIS_MODULE;

	indio_dev->pollfunc = kzalloc(sizeof(*indio_dev->pollfunc), GFP_KERNEL);
	if (indio_dev->pollfunc == NULL) {
		ret = -ENOMEM;
		goto error_iio_sw_rb_free;;
	}
	indio_dev->pollfunc->poll_func_main = &lis3l02dq_poll_func_th;
	indio_dev->pollfunc->private_data = indio_dev;
	indio_dev->modes |= INDIO_RING_TRIGGERED;
	return 0;

error_iio_sw_rb_free:
	iio_sw_rb_free(indio_dev->ring);
	return ret;
}