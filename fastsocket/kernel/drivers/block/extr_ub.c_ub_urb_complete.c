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
struct urb {struct ub_dev* context; } ;
struct ub_dev {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  work_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ub_complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ub_urb_complete(struct urb *urb)
{
	struct ub_dev *sc = urb->context;

	ub_complete(&sc->work_done);
	tasklet_schedule(&sc->tasklet);
}