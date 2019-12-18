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
typedef  int u8 ;
struct sca3000_state {int bpse; int /*<<< orphan*/  lock; } ;
struct iio_ring_buffer {int dummy; } ;
struct iio_hw_ring_buffer {struct iio_dev* private; } ;
struct iio_dev {struct sca3000_state* dev_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_REG_ADDR_BUF_COUNT ; 
 int /*<<< orphan*/  SCA3000_REG_ADDR_RING_OUT ; 
 struct iio_hw_ring_buffer* iio_to_hw_ring_buf (struct iio_ring_buffer*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_data (struct sca3000_state*,int /*<<< orphan*/ ,int**,int) ; 

__attribute__((used)) static int sca3000_rip_hw_rb(struct iio_ring_buffer *r,
			     size_t count, u8 **data, int *dead_offset)
{
	struct iio_hw_ring_buffer *hw_ring = iio_to_hw_ring_buf(r);
	struct iio_dev *indio_dev = hw_ring->private;
	struct sca3000_state *st = indio_dev->dev_data;
	u8 *rx;
	int ret, num_available, num_read = 0;
	int bytes_per_sample = 1;

	if (st->bpse == 11)
		bytes_per_sample = 2;

	mutex_lock(&st->lock);
	/* Check how much data is available:
	 * RFC: Implement an ioctl to not bother checking whether there
	 * is enough data in the ring?  Afterall, if we are responding
	 * to an interrupt we have a minimum content guaranteed so it
	 * seems slight silly to waste time checking it is there.
	 */
	ret = sca3000_read_data(st,
				SCA3000_REG_ADDR_BUF_COUNT,
				&rx, 1);
	if (ret)
		goto error_ret;
	else
		num_available = rx[1];
	/* num_available is the total number of samples available
	 * i.e. number of time points * number of channels.
	 */
	kfree(rx);
	if (count > num_available * bytes_per_sample)
		num_read = num_available*bytes_per_sample;
	else
		num_read = count - (count % (bytes_per_sample));

	/* Avoid the read request byte */
	*dead_offset = 1;
	ret = sca3000_read_data(st,
				SCA3000_REG_ADDR_RING_OUT,
				data, num_read);
error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : num_read;
}