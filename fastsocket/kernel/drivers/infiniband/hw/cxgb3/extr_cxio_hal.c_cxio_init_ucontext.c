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
struct cxio_ucontext {int /*<<< orphan*/  lock; int /*<<< orphan*/  qpids; } ;
struct cxio_rdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void cxio_init_ucontext(struct cxio_rdev *rdev_p, struct cxio_ucontext *uctx)
{
	INIT_LIST_HEAD(&uctx->qpids);
	mutex_init(&uctx->lock);
}