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
struct iio_ring_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIO_EVENT_CODE_RING_50_FULL ; 
 int /*<<< orphan*/  IIO_EVENT_CODE_RING_75_FULL ; 
 int SCA3000_INT_STATUS_HALF ; 
 int SCA3000_INT_STATUS_THREE_QUARTERS ; 
 int /*<<< orphan*/  iio_push_or_escallate_ring_event (struct iio_ring_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_push_ring_event (struct iio_ring_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sca3000_ring_int_process(u8 val, struct iio_ring_buffer *ring)
{
	if (val & SCA3000_INT_STATUS_THREE_QUARTERS)
		iio_push_or_escallate_ring_event(ring,
						 IIO_EVENT_CODE_RING_75_FULL,
						 0);
	else if (val & SCA3000_INT_STATUS_HALF)
		iio_push_ring_event(ring,
				    IIO_EVENT_CODE_RING_50_FULL, 0);
}