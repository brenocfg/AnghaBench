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
 int /*<<< orphan*/  BR_SSL_SENDAPP ; 
 int /*<<< orphan*/  br_ssl_engine_sendapp_ack (int /*<<< orphan*/ ,size_t) ; 
 unsigned char* br_ssl_engine_sendapp_buf (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,size_t) ; 
 scalar_t__ run_until (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
br_sslio_write(br_sslio_context *ctx, const void *src, size_t len)
{
	unsigned char *buf;
	size_t alen;

	if (len == 0) {
		return 0;
	}
	if (run_until(ctx, BR_SSL_SENDAPP) < 0) {
		return -1;
	}
	buf = br_ssl_engine_sendapp_buf(ctx->engine, &alen);
	if (alen > len) {
		alen = len;
	}
	memcpy(buf, src, alen);
	br_ssl_engine_sendapp_ack(ctx->engine, alen);
	return (int)alen;
}