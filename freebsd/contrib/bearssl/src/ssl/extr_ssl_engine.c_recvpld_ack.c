#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t ixa; size_t ixb; scalar_t__ ixc; } ;
typedef  TYPE_1__ br_ssl_engine_context ;

/* Variables and functions */
 int /*<<< orphan*/  make_ready_in (TYPE_1__*) ; 

__attribute__((used)) static void
recvpld_ack(br_ssl_engine_context *rc, size_t len)
{
	rc->ixa += len;

	/*
	 * If we read all the available data, then we either expect
	 * the remainder of the current record (if the current record
	 * was not finished; this may happen when encryption is not
	 * active), or go to "ready" state.
	 */
	if (rc->ixa == rc->ixb) {
		if (rc->ixc == 0) {
			make_ready_in(rc);
		} else {
			rc->ixa = rc->ixb = 5;
		}
	}
}