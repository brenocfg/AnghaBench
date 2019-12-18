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
struct iser_conn {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iser_conn_release (struct iser_conn*,int) ; 

int iser_conn_put(struct iser_conn *ib_conn, int can_destroy_id)
{
	if (atomic_dec_and_test(&ib_conn->refcount)) {
		iser_conn_release(ib_conn, can_destroy_id);
		return 1;
	}
	return 0;
}