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
struct TYPE_7__ {size_t minlen; size_t maclen; int /*<<< orphan*/  cipher_ctx_enc; } ;
typedef  TYPE_2__ mbedtls_ssl_transform ;
struct TYPE_8__ {TYPE_1__* session_out; TYPE_2__* transform_out; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_6__ {scalar_t__ compression; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE ; 
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
#define  MBEDTLS_MODE_CBC 131 
#define  MBEDTLS_MODE_CCM 130 
#define  MBEDTLS_MODE_GCM 129 
#define  MBEDTLS_MODE_STREAM 128 
 scalar_t__ MBEDTLS_SSL_COMPRESS_NULL ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 size_t mbedtls_cipher_get_block_size (int /*<<< orphan*/ *) ; 
 int mbedtls_cipher_get_cipher_mode (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_ssl_hdr_len (TYPE_3__ const*) ; 

int mbedtls_ssl_get_record_expansion( const mbedtls_ssl_context *ssl )
{
    size_t transform_expansion;
    const mbedtls_ssl_transform *transform = ssl->transform_out;

#if defined(MBEDTLS_ZLIB_SUPPORT)
    if( ssl->session_out->compression != MBEDTLS_SSL_COMPRESS_NULL )
        return( MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE );
#endif

    if( transform == NULL )
        return( (int) mbedtls_ssl_hdr_len( ssl ) );

    switch( mbedtls_cipher_get_cipher_mode( &transform->cipher_ctx_enc ) )
    {
        case MBEDTLS_MODE_GCM:
        case MBEDTLS_MODE_CCM:
        case MBEDTLS_MODE_STREAM:
            transform_expansion = transform->minlen;
            break;

        case MBEDTLS_MODE_CBC:
            transform_expansion = transform->maclen
                      + mbedtls_cipher_get_block_size( &transform->cipher_ctx_enc );
            break;

        default:
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

    return( (int)( mbedtls_ssl_hdr_len( ssl ) + transform_expansion ) );
}