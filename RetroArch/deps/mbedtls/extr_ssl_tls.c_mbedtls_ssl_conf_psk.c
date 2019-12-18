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
struct TYPE_3__ {unsigned char* psk; unsigned char* psk_identity; size_t psk_len; size_t psk_identity_len; } ;
typedef  TYPE_1__ mbedtls_ssl_config ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_ALLOC_FAILED ; 
 int MBEDTLS_ERR_SSL_BAD_INPUT_DATA ; 
 size_t MBEDTLS_PSK_MAX_LEN ; 
 size_t MBEDTLS_SSL_MAX_CONTENT_LEN ; 
 scalar_t__ mbedtls_calloc (int,size_t) ; 
 int /*<<< orphan*/  mbedtls_free (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 

int mbedtls_ssl_conf_psk( mbedtls_ssl_config *conf,
                const unsigned char *psk, size_t psk_len,
                const unsigned char *psk_identity, size_t psk_identity_len )
{
    if( psk == NULL || psk_identity == NULL )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    if( psk_len > MBEDTLS_PSK_MAX_LEN )
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );

    /* Identity len will be encoded on two bytes */
    if( ( psk_identity_len >> 16 ) != 0 ||
        psk_identity_len > MBEDTLS_SSL_MAX_CONTENT_LEN )
    {
        return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );
    }

    if( conf->psk != NULL || conf->psk_identity != NULL )
    {
        mbedtls_free( conf->psk );
        mbedtls_free( conf->psk_identity );
        conf->psk = NULL;
        conf->psk_identity = NULL;
    }

    if( ( conf->psk = (unsigned char*)mbedtls_calloc( 1, psk_len ) ) == NULL ||
        ( conf->psk_identity = (unsigned char*)mbedtls_calloc( 1, psk_identity_len ) ) == NULL )
    {
        mbedtls_free( conf->psk );
        mbedtls_free( conf->psk_identity );
        conf->psk = NULL;
        conf->psk_identity = NULL;
        return( MBEDTLS_ERR_SSL_ALLOC_FAILED );
    }

    conf->psk_len = psk_len;
    conf->psk_identity_len = psk_identity_len;

    memcpy( conf->psk, psk, conf->psk_len );
    memcpy( conf->psk_identity, psk_identity, conf->psk_identity_len );

    return( 0 );
}