#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_2__ {size_t w_nr; } ;
struct rds_ib_connection {int /*<<< orphan*/ * i_recvs; TYPE_1__ i_recv_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  rds_ib_recv_clear_one (struct rds_ib_connection*,int /*<<< orphan*/ *) ; 

void rds_ib_recv_clear_ring(struct rds_ib_connection *ic)
{
	u32 i;

	for (i = 0; i < ic->i_recv_ring.w_nr; i++)
		rds_ib_recv_clear_one(ic, &ic->i_recvs[i]);
}