#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ minor_ver; int split_done; TYPE_1__* transform_out; TYPE_2__* conf; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_7__ {scalar_t__ cbc_record_splitting; } ;
struct TYPE_6__ {int /*<<< orphan*/  cipher_ctx_enc; } ;

/* Variables and functions */
 scalar_t__ MBEDTLS_MODE_CBC ; 
 scalar_t__ MBEDTLS_SSL_CBC_RECORD_SPLITTING_DISABLED ; 
 scalar_t__ MBEDTLS_SSL_MINOR_VERSION_1 ; 
 scalar_t__ mbedtls_cipher_get_cipher_mode (int /*<<< orphan*/ *) ; 
 int ssl_write_real (TYPE_3__*,unsigned char const*,size_t) ; 

__attribute__((used)) static int ssl_write_split( mbedtls_ssl_context *ssl,
                            const unsigned char *buf, size_t len )
{
    int ret;

    if( ssl->conf->cbc_record_splitting ==
            MBEDTLS_SSL_CBC_RECORD_SPLITTING_DISABLED ||
        len <= 1 ||
        ssl->minor_ver > MBEDTLS_SSL_MINOR_VERSION_1 ||
        mbedtls_cipher_get_cipher_mode( &ssl->transform_out->cipher_ctx_enc )
                                != MBEDTLS_MODE_CBC )
    {
        return( ssl_write_real( ssl, buf, len ) );
    }

    if( ssl->split_done == 0 )
    {
        if( ( ret = ssl_write_real( ssl, buf, 1 ) ) <= 0 )
            return( ret );
        ssl->split_done = 1;
    }

    if( ( ret = ssl_write_real( ssl, buf + 1, len - 1 ) ) <= 0 )
        return( ret );
    ssl->split_done = 0;

    return( ret + 1 );
}