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
struct TYPE_3__ {int /*<<< orphan*/  sockfd; scalar_t__ ssl; } ;
typedef  TYPE_1__ ws_ctx_t ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_write (scalar_t__,void const*,size_t) ; 
 int /*<<< orphan*/  send (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 

ssize_t ws_send(ws_ctx_t *ctx, const void *buf, size_t len) {
    if (ctx->ssl) {
        //handler_msg("SSL send\n");
        return SSL_write(ctx->ssl, buf, len);
    } else {
        return send(ctx->sockfd, buf, len, 0);
    }
}