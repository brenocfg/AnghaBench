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
struct TYPE_3__ {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * type; } ;
struct iio_ring_buffer {TYPE_1__ dev; } ;
struct iio_hw_ring_buffer {struct iio_ring_buffer buf; struct iio_dev* private; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  iio_ring_buffer_init (struct iio_ring_buffer*,struct iio_dev*) ; 
 struct iio_hw_ring_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sca3000_ring_type ; 

__attribute__((used)) static struct iio_ring_buffer *sca3000_rb_allocate(struct iio_dev *indio_dev)
{
	struct iio_ring_buffer *buf;
	struct iio_hw_ring_buffer *ring;

	ring = kzalloc(sizeof *ring, GFP_KERNEL);
	if (!ring)
		return 0;
	ring->private = indio_dev;
	buf = &ring->buf;
	iio_ring_buffer_init(buf, indio_dev);
	buf->dev.type = &sca3000_ring_type;
	device_initialize(&buf->dev);
	buf->dev.parent = &indio_dev->dev;
	dev_set_drvdata(&buf->dev, (void *)buf);

	return buf;
}