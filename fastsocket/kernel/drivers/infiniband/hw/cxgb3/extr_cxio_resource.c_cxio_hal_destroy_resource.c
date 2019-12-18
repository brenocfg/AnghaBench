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
struct cxio_hal_resource {int /*<<< orphan*/  pdid_fifo; int /*<<< orphan*/  qpid_fifo; int /*<<< orphan*/  cqid_fifo; int /*<<< orphan*/  tpt_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cxio_hal_resource*) ; 

void cxio_hal_destroy_resource(struct cxio_hal_resource *rscp)
{
	kfifo_free(rscp->tpt_fifo);
	kfifo_free(rscp->cqid_fifo);
	kfifo_free(rscp->qpid_fifo);
	kfifo_free(rscp->pdid_fifo);
	kfree(rscp);
}