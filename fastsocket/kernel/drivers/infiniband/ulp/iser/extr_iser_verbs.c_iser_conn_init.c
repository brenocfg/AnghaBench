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
struct iser_conn {int /*<<< orphan*/  lock; int /*<<< orphan*/  conn_list; int /*<<< orphan*/  refcount; int /*<<< orphan*/  post_send_buf_count; scalar_t__ post_recv_buf_count; int /*<<< orphan*/  wait; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISER_CONN_INIT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void iser_conn_init(struct iser_conn *ib_conn)
{
	ib_conn->state = ISER_CONN_INIT;
	init_waitqueue_head(&ib_conn->wait);
	ib_conn->post_recv_buf_count = 0;
	atomic_set(&ib_conn->post_send_buf_count, 0);
	atomic_set(&ib_conn->refcount, 1); /* ref ib conn allocation */
	INIT_LIST_HEAD(&ib_conn->conn_list);
	spin_lock_init(&ib_conn->lock);
}