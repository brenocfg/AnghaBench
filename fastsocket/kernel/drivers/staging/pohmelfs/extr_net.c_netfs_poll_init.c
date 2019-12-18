#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netfs_state {TYPE_2__* socket; } ;
struct netfs_poll_helper {int /*<<< orphan*/  pt; struct netfs_state* st; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* poll ) (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  init_poll_funcptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netfs_queue_func ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netfs_poll_init(struct netfs_state *st)
{
	struct netfs_poll_helper ph;

	ph.st = st;
	init_poll_funcptr(&ph.pt, &netfs_queue_func);

	st->socket->ops->poll(NULL, st->socket, &ph.pt);
	return 0;
}