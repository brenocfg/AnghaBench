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
struct iio_dev {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  sca3000_rb_free (int /*<<< orphan*/ ) ; 

void sca3000_unconfigure_ring(struct iio_dev *indio_dev)
{
	sca3000_rb_free(indio_dev->ring);
}