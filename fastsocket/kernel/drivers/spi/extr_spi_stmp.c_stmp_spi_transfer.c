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
struct stmp_spi {int /*<<< orphan*/  lock; int /*<<< orphan*/  work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  queue; } ;
struct spi_message {int /*<<< orphan*/  queue; int /*<<< orphan*/  status; } ;
struct spi_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct stmp_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int stmp_spi_transfer(struct spi_device *spi, struct spi_message *m)
{
	struct stmp_spi *ss = spi_master_get_devdata(spi->master);
	unsigned long flags;

	m->status = -EINPROGRESS;
	spin_lock_irqsave(&ss->lock, flags);
	list_add_tail(&m->queue, &ss->queue);
	queue_work(ss->workqueue, &ss->work);
	spin_unlock_irqrestore(&ss->lock, flags);
	return 0;
}