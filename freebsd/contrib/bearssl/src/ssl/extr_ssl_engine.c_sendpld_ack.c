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
struct TYPE_4__ {scalar_t__ iomode; scalar_t__ ibuf; scalar_t__ obuf; scalar_t__ oxa; scalar_t__ oxb; } ;
typedef  TYPE_1__ br_ssl_engine_context ;

/* Variables and functions */
 scalar_t__ BR_IO_INOUT ; 
 scalar_t__ BR_IO_OUT ; 
 int /*<<< orphan*/  sendpld_flush (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sendpld_ack(br_ssl_engine_context *rc, size_t len)
{
	/*
	 * If using a shared buffer, then we may have to modify the
	 * current mode.
	 */
	if (rc->iomode == BR_IO_INOUT && rc->ibuf == rc->obuf) {
		rc->iomode = BR_IO_OUT;
	}
	rc->oxa += len;
	if (rc->oxa >= rc->oxb) {
		/*
		 * Set oxb to one more than oxa so that sendpld_flush()
		 * does not mistakingly believe that a record is
		 * already prepared and being sent.
		 */
		rc->oxb = rc->oxa + 1;
		sendpld_flush(rc, 0);
	}
}