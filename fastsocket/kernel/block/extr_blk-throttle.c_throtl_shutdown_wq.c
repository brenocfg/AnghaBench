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
struct throtl_data {int /*<<< orphan*/  throtl_work; } ;
struct request_queue {struct throtl_data* td; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void throtl_shutdown_wq(struct request_queue *q)
{
	struct throtl_data *td = q->td;

	cancel_delayed_work_sync(&td->throtl_work);
}