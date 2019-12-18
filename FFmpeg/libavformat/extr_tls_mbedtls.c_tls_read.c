#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {int /*<<< orphan*/  ssl_context; } ;
typedef  TYPE_2__ TLSContext ;

/* Variables and functions */
 int handle_tls_error (TYPE_1__*,char*,int) ; 
 int mbedtls_ssl_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tls_read(URLContext *h, uint8_t *buf, int size)
{
    TLSContext *tls_ctx = h->priv_data;
    int ret;

    if ((ret = mbedtls_ssl_read(&tls_ctx->ssl_context, buf, size)) > 0) {
        // return read length
        return ret;
    }

    return handle_tls_error(h, "mbedtls_ssl_read", ret);
}