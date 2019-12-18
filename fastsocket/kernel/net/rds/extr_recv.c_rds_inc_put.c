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
struct rds_incoming {TYPE_2__* i_conn; int /*<<< orphan*/  i_item; int /*<<< orphan*/  i_refcount; } ;
struct TYPE_4__ {TYPE_1__* c_trans; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* inc_free ) (struct rds_incoming*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_incoming*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rds_incoming*) ; 

void rds_inc_put(struct rds_incoming *inc)
{
	rdsdebug("put inc %p ref %d\n", inc, atomic_read(&inc->i_refcount));
	if (atomic_dec_and_test(&inc->i_refcount)) {
		BUG_ON(!list_empty(&inc->i_item));

		inc->i_conn->c_trans->inc_free(inc);
	}
}