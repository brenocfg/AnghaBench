#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t hlen; int /*<<< orphan*/  cpu; void const* hbuf; scalar_t__ event; } ;
typedef  TYPE_1__ br_pem_decoder_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_pem_decoder_run (int /*<<< orphan*/ *) ; 

size_t
br_pem_decoder_push(br_pem_decoder_context *ctx,
	const void *data, size_t len)
{
	if (ctx->event) {
		return 0;
	}
	ctx->hbuf = data;
	ctx->hlen = len;
	br_pem_decoder_run(&ctx->cpu);
	return len - ctx->hlen;
}