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
struct module {int dummy; } ;
struct TYPE_2__ {int id; int /*<<< orphan*/  _name; } ;
struct iio_ring_buffer {TYPE_1__ ev_int; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_free_idr_val (int /*<<< orphan*/ *,int) ; 
 int iio_get_new_idr_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_ring_event_idr ; 
 int iio_setup_ev_int (TYPE_1__*,int /*<<< orphan*/ ,struct module*,struct device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static inline int
__iio_request_ring_buffer_event_chrdev(struct iio_ring_buffer *buf,
				       int id,
				       struct module *owner,
				       struct device *dev)
{
	int ret;
	ret = iio_get_new_idr_val(&iio_ring_event_idr);
	if (ret < 0)
		goto error_ret;
	else
		buf->ev_int.id = ret;

	snprintf(buf->ev_int._name, 20,
		 "ring_event_line%d",
		 buf->ev_int.id);
	ret = iio_setup_ev_int(&(buf->ev_int),
			       buf->ev_int._name,
			       owner,
			       dev);
	if (ret)
		goto error_free_id;
	return 0;

error_free_id:
	iio_free_idr_val(&iio_ring_event_idr, buf->ev_int.id);
error_ret:
	return ret;
}