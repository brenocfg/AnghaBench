#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iio_shared_ev_pointer {struct iio_detected_event_list* ev_p; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct iio_event_interface {scalar_t__ current_events; scalar_t__ max_events; int /*<<< orphan*/  event_list_lock; int /*<<< orphan*/  wait; TYPE_3__ det_events; TYPE_1__ handler; } ;
struct TYPE_5__ {int id; int /*<<< orphan*/  timestamp; } ;
struct iio_detected_event_list {int /*<<< orphan*/  list; struct iio_shared_ev_pointer* shared_pointer; TYPE_2__ ev; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IIO_BUSY_BIT_POS ; 
 struct iio_detected_event_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int __iio_push_event(struct iio_event_interface *ev_int,
		     int ev_code,
		     s64 timestamp,
		     struct iio_shared_ev_pointer *
		     shared_pointer_p)
{
	struct iio_detected_event_list *ev;
	int ret = 0;

	/* Does anyone care? */
	mutex_lock(&ev_int->event_list_lock);
	if (test_bit(IIO_BUSY_BIT_POS, &ev_int->handler.flags)) {
		if (ev_int->current_events == ev_int->max_events)
			return 0;
		ev = kmalloc(sizeof(*ev), GFP_KERNEL);
		if (ev == NULL) {
			ret = -ENOMEM;
			goto error_ret;
		}
		ev->ev.id = ev_code;
		ev->ev.timestamp = timestamp;
		ev->shared_pointer = shared_pointer_p;
		if (ev->shared_pointer)
			shared_pointer_p->ev_p = ev;

		list_add_tail(&ev->list, &ev_int->det_events.list);
		ev_int->current_events++;
		mutex_unlock(&ev_int->event_list_lock);
		wake_up_interruptible(&ev_int->wait);
	} else
		mutex_unlock(&ev_int->event_list_lock);

error_ret:
	return ret;
}