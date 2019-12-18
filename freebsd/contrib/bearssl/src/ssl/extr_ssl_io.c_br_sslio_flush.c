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
struct TYPE_4__ {int /*<<< orphan*/  engine; } ;
typedef  TYPE_1__ br_sslio_context ;

/* Variables and functions */
 int BR_SSL_RECVAPP ; 
 int BR_SSL_SENDAPP ; 
 int /*<<< orphan*/  br_ssl_engine_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int run_until (TYPE_1__*,int) ; 

int
br_sslio_flush(br_sslio_context *ctx)
{
	/*
	 * We trigger a flush. We know the data is gone when there is
	 * no longer any record data to send, and we can either read
	 * or write application data. The call to run_until() does the
	 * job because it ensures that any assembled record data is
	 * first sent down the wire before considering anything else.
	 */
	br_ssl_engine_flush(ctx->engine, 0);
	return run_until(ctx, BR_SSL_SENDAPP | BR_SSL_RECVAPP);
}