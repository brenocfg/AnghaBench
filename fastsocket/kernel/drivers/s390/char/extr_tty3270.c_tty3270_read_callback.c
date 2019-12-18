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
struct tty3270 {int /*<<< orphan*/  readlet; } ;
struct raw3270_request {scalar_t__ view; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw3270_get_view (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tty3270_read_callback(struct raw3270_request *rq, void *data)
{
	raw3270_get_view(rq->view);
	/* Schedule tasklet to pass input to tty. */
	tasklet_schedule(&((struct tty3270 *) rq->view)->readlet);
}