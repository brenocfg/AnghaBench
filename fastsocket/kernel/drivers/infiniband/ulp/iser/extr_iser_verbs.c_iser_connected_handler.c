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
struct rdma_cm_id {scalar_t__ context; } ;
struct iser_conn {int /*<<< orphan*/  wait; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_CONN_UP ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iser_connected_handler(struct rdma_cm_id *cma_id)
{
	struct iser_conn *ib_conn;

	ib_conn = (struct iser_conn *)cma_id->context;
	ib_conn->state = ISER_CONN_UP;
	wake_up_interruptible(&ib_conn->wait);
}