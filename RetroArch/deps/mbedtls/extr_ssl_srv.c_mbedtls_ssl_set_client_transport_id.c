#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t cli_id_len; int /*<<< orphan*/ * cli_id; TYPE_1__* conf; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
struct TYPE_4__ {scalar_t__ endpoint; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_ALLOC_FAILED ; 
 int MBEDTLS_ERR_SSL_BAD_INPUT_DATA ; 
 scalar_t__ MBEDTLS_SSL_IS_SERVER ; 
 int /*<<< orphan*/ * mbedtls_calloc (int,size_t) ; 
 int /*<<< orphan*/  mbedtls_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int mbedtls_ssl_set_client_transport_id( mbedtls_ssl_context *ssl,
                                 const unsigned char *info,
                                 size_t ilen )
{
    if( ssl->conf->endpoint != MBEDTLS_SSL_IS_SERVER )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    mbedtls_free( ssl->cli_id );

    if( ( ssl->cli_id = mbedtls_calloc( 1, ilen ) ) == NULL )
        return( MBEDTLS_ERR_SSL_ALLOC_FAILED );

    memcpy( ssl->cli_id, info, ilen );
    ssl->cli_id_len = ilen;

    return( 0 );
}