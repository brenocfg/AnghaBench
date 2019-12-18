#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_ssl_context ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE ; 
 int MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 

__attribute__((used)) static int ssl_parse_server_psk_hint( mbedtls_ssl_context *ssl,
                                      unsigned char **p,
                                      unsigned char *end )
{
    int ret = MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE;
    size_t  len;
    ((void) ssl);

    /*
     * PSK parameters:
     *
     * opaque psk_identity_hint<0..2^16-1>;
     */
    len = (*p)[0] << 8 | (*p)[1];
    *p += 2;

    if( (*p) + len > end )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad server key exchange message "
                                    "(psk_identity_hint length)" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE );
    }

    /*
     * Note: we currently ignore the PKS identity hint, as we only allow one
     * PSK to be provisionned on the client. This could be changed later if
     * someone needs that feature.
     */
    *p += len;
    ret = 0;

    return( ret );
}