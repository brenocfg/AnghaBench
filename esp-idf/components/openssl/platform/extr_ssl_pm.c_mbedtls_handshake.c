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
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ mbedtls_ssl_context ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_SSL_HANDSHAKE_OVER ; 
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_PLATFORM_DEBUG_LEVEL ; 
 int mbedtls_ssl_handshake_step (TYPE_1__*) ; 

__attribute__((used)) static int mbedtls_handshake( mbedtls_ssl_context *ssl )
{
    int ret = 0;

    while (ssl->state != MBEDTLS_SSL_HANDSHAKE_OVER) {
        ret = mbedtls_ssl_handshake_step(ssl);

        SSL_DEBUG(SSL_PLATFORM_DEBUG_LEVEL, "ssl ret %d state %d", ret, ssl->state);

        if (ret != 0)
            break;
    }

    return ret;
}