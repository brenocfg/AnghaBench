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
struct TYPE_5__ {scalar_t__ minor_ver; TYPE_1__* handshake; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
struct TYPE_4__ {int /*<<< orphan*/  calc_verify; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_INVALID_VERIFY_HASH ; 
#define  MBEDTLS_SSL_HASH_MD5 131 
#define  MBEDTLS_SSL_HASH_SHA1 130 
#define  MBEDTLS_SSL_HASH_SHA256 129 
#define  MBEDTLS_SSL_HASH_SHA384 128 
 scalar_t__ MBEDTLS_SSL_MINOR_VERSION_3 ; 
 int /*<<< orphan*/  ssl_calc_verify_tls ; 
 int /*<<< orphan*/  ssl_calc_verify_tls_sha256 ; 
 int /*<<< orphan*/  ssl_calc_verify_tls_sha384 ; 

int mbedtls_ssl_set_calc_verify_md( mbedtls_ssl_context *ssl, int md )
{
#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
    if( ssl->minor_ver != MBEDTLS_SSL_MINOR_VERSION_3 )
        return MBEDTLS_ERR_SSL_INVALID_VERIFY_HASH;

    switch( md )
    {
#if defined(MBEDTLS_SSL_PROTO_TLS1) || defined(MBEDTLS_SSL_PROTO_TLS1_1)
#if defined(MBEDTLS_MD5_C)
        case MBEDTLS_SSL_HASH_MD5:
            return MBEDTLS_ERR_SSL_INVALID_VERIFY_HASH;
#endif
#if defined(MBEDTLS_SHA1_C)
        case MBEDTLS_SSL_HASH_SHA1:
            ssl->handshake->calc_verify = ssl_calc_verify_tls;
            break;
#endif
#endif /* MBEDTLS_SSL_PROTO_TLS1 || MBEDTLS_SSL_PROTO_TLS1_1 */
#if defined(MBEDTLS_SHA512_C)
        case MBEDTLS_SSL_HASH_SHA384:
            ssl->handshake->calc_verify = ssl_calc_verify_tls_sha384;
            break;
#endif
#if defined(MBEDTLS_SHA256_C)
        case MBEDTLS_SSL_HASH_SHA256:
            ssl->handshake->calc_verify = ssl_calc_verify_tls_sha256;
            break;
#endif
        default:
            return MBEDTLS_ERR_SSL_INVALID_VERIFY_HASH;
    }

    return 0;
#else /* !MBEDTLS_SSL_PROTO_TLS1_2 */
    (void) ssl;
    (void) md;

    return MBEDTLS_ERR_SSL_INVALID_VERIFY_HASH;
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */
}