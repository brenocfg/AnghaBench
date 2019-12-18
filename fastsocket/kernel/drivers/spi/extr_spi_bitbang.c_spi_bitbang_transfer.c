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
struct spi_message {int /*<<< orphan*/  queue; int /*<<< orphan*/  status; scalar_t__ actual_length; } ;
struct spi_device {int /*<<< orphan*/  max_speed_hz; int /*<<< orphan*/  master; } ;
struct spi_bitbang {int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct spi_bitbang* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int spi_bitbang_transfer(struct spi_device *spi, struct spi_message *m)
{
	struct spi_bitbang	*bitbang;
	unsigned long		flags;
	int			status = 0;

	m->actual_length = 0;
	m->status = -EINPROGRESS;

	bitbang = spi_master_get_devdata(spi->master);

	spin_lock_irqsave(&bitbang->lock, flags);
	if (!spi->max_speed_hz)
		status = -ENETDOWN;
	else {
		list_add_tail(&m->queue, &bitbang->queue);
		queue_work(bitbang->workqueue, &bitbang->work);
	}
	spin_unlock_irqrestore(&bitbang->lock, flags);

	return status;
}