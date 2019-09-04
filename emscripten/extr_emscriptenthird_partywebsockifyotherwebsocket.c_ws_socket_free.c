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
struct TYPE_3__ {scalar_t__ sockfd; int /*<<< orphan*/ * ssl_ctx; int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_1__ ws_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  shutdown (scalar_t__,int /*<<< orphan*/ ) ; 

int ws_socket_free(ws_ctx_t *ctx) {
    if (ctx->ssl) {
        SSL_free(ctx->ssl);
        ctx->ssl = NULL;
    }
    if (ctx->ssl_ctx) {
        SSL_CTX_free(ctx->ssl_ctx);
        ctx->ssl_ctx = NULL;
    }
    if (ctx->sockfd) {
        shutdown(ctx->sockfd, SHUT_RDWR);
        close(ctx->sockfd);
        ctx->sockfd = 0;
    }
}