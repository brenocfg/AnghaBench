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
struct TYPE_4__ {size_t max_packet_size; } ;
typedef  TYPE_1__ URLContext ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  MBEDTLS_ERR_SSL_WANT_READ ; 
 int ffurl_read (TYPE_1__*,unsigned char*,size_t) ; 
 int handle_transport_error (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mbedtls_recv(void *ctx, unsigned char *buf, size_t len)
{
    URLContext *h = (URLContext*) ctx;
    int ret = ffurl_read(h, buf, len);
    if (ret >= 0)
        return ret;

    if (h->max_packet_size && len > h->max_packet_size)
        return MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL;

    return handle_transport_error(h, "ffurl_read", MBEDTLS_ERR_SSL_WANT_READ, ret);
}