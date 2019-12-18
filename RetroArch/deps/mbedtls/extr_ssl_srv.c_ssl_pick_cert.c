#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {TYPE_6__* cert; int /*<<< orphan*/  key; struct TYPE_10__* next; } ;
typedef  TYPE_3__ mbedtls_ssl_key_cert ;
struct TYPE_11__ {scalar_t__ minor_ver; TYPE_2__* handshake; TYPE_1__* conf; } ;
typedef  TYPE_4__ mbedtls_ssl_context ;
typedef  int /*<<< orphan*/  mbedtls_ssl_ciphersuite_t ;
typedef  scalar_t__ mbedtls_pk_type_t ;
struct TYPE_12__ {scalar_t__ sig_md; } ;
struct TYPE_9__ {TYPE_3__* key_cert; int /*<<< orphan*/  curves; TYPE_3__* sni_key_cert; } ;
struct TYPE_8__ {TYPE_3__* key_cert; } ;

/* Variables and functions */
 scalar_t__ MBEDTLS_MD_SHA1 ; 
 scalar_t__ MBEDTLS_PK_ECDSA ; 
 scalar_t__ MBEDTLS_PK_NONE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_CRT (int,char*,TYPE_6__*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_IS_SERVER ; 
 scalar_t__ MBEDTLS_SSL_MINOR_VERSION_3 ; 
 int /*<<< orphan*/  mbedtls_pk_can_do (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mbedtls_ssl_check_cert_usage (TYPE_6__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_ssl_get_ciphersuite_sig_pk_alg (int /*<<< orphan*/  const*) ; 
 scalar_t__ ssl_check_key_curve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_pick_cert( mbedtls_ssl_context *ssl,
                          const mbedtls_ssl_ciphersuite_t * ciphersuite_info )
{
    mbedtls_ssl_key_cert *cur, *list, *fallback = NULL;
    mbedtls_pk_type_t pk_alg =
        mbedtls_ssl_get_ciphersuite_sig_pk_alg( ciphersuite_info );
    uint32_t flags;

#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
    if( ssl->handshake->sni_key_cert != NULL )
        list = ssl->handshake->sni_key_cert;
    else
#endif
        list = ssl->conf->key_cert;

    if( pk_alg == MBEDTLS_PK_NONE )
        return( 0 );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite requires certificate" ) );

    if( list == NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "server has no certificate" ) );
        return( -1 );
    }

    for( cur = list; cur != NULL; cur = cur->next )
    {
        MBEDTLS_SSL_DEBUG_CRT( 3, "candidate certificate chain, certificate",
                          cur->cert );

        if( ! mbedtls_pk_can_do( cur->key, pk_alg ) )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "certificate mismatch: key type" ) );
            continue;
        }

        /*
         * This avoids sending the client a cert it'll reject based on
         * keyUsage or other extensions.
         *
         * It also allows the user to provision different certificates for
         * different uses based on keyUsage, eg if they want to avoid signing
         * and decrypting with the same RSA key.
         */
        if( mbedtls_ssl_check_cert_usage( cur->cert, ciphersuite_info,
                                  MBEDTLS_SSL_IS_SERVER, &flags ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "certificate mismatch: "
                                "(extended) key usage extension" ) );
            continue;
        }

#if defined(MBEDTLS_ECDSA_C)
        if( pk_alg == MBEDTLS_PK_ECDSA &&
            ssl_check_key_curve( cur->key, ssl->handshake->curves ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "certificate mismatch: elliptic curve" ) );
            continue;
        }
#endif

        /*
         * Try to select a SHA-1 certificate for pre-1.2 clients, but still
         * present them a SHA-higher cert rather than failing if it's the only
         * one we got that satisfies the other conditions.
         */
        if( ssl->minor_ver < MBEDTLS_SSL_MINOR_VERSION_3 &&
            cur->cert->sig_md != MBEDTLS_MD_SHA1 )
        {
            if( fallback == NULL )
                fallback = cur;
            {
                MBEDTLS_SSL_DEBUG_MSG( 3, ( "certificate not preferred: "
                                    "sha-2 with pre-TLS 1.2 client" ) );
            continue;
            }
        }

        /* If we get there, we got a winner */
        break;
    }

    if( cur == NULL )
        cur = fallback;

    /* Do not update ssl->handshake->key_cert unless there is a match */
    if( cur != NULL )
    {
        ssl->handshake->key_cert = cur;
        MBEDTLS_SSL_DEBUG_CRT( 3, "selected certificate chain, certificate",
                          ssl->handshake->key_cert->cert );
        return( 0 );
    }

    return( -1 );
}