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
 scalar_t__ BR_ERR_OK ; 
 scalar_t__ BR_SSL_CLOSED ; 
 int /*<<< orphan*/  BR_SSL_RECVAPP ; 
 int /*<<< orphan*/  br_ssl_engine_close (int /*<<< orphan*/ ) ; 
 scalar_t__ br_ssl_engine_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ br_ssl_engine_last_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ssl_engine_recvapp_ack (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * br_ssl_engine_recvapp_buf (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  run_until (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
br_sslio_close(br_sslio_context *ctx)
{
	br_ssl_engine_close(ctx->engine);
	while (br_ssl_engine_current_state(ctx->engine) != BR_SSL_CLOSED) {
		/*
		 * Discard any incoming application data.
		 */
		size_t len;

		run_until(ctx, BR_SSL_RECVAPP);
		if (br_ssl_engine_recvapp_buf(ctx->engine, &len) != NULL) {
			br_ssl_engine_recvapp_ack(ctx->engine, len);
		}
	}
	return br_ssl_engine_last_error(ctx->engine) == BR_ERR_OK;
}