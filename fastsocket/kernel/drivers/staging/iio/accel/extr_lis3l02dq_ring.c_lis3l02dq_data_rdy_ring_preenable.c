#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int scan_count; TYPE_2__* ring; scalar_t__ scan_timestamp; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_bpd ) (TYPE_2__*,size_t) ;} ;
struct TYPE_4__ {TYPE_1__ access; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t) ; 

__attribute__((used)) static int lis3l02dq_data_rdy_ring_preenable(struct iio_dev *indio_dev)
{
	size_t size;
	/* Check if there are any scan elements enabled, if not fail*/
	if (!(indio_dev->scan_count || indio_dev->scan_timestamp))
		return -EINVAL;

	if (indio_dev->ring->access.set_bpd) {
		if (indio_dev->scan_timestamp)
			if (indio_dev->scan_count) /* Timestamp and data */
				size = 2*sizeof(s64);
			else /* Timestamp only  */
				size = sizeof(s64);
		else /* Data only */
			size = indio_dev->scan_count*sizeof(s16);
		indio_dev->ring->access.set_bpd(indio_dev->ring, size);
	}

	return 0;
}