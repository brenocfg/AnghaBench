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
struct TYPE_4__ {int /*<<< orphan*/ * ticket; int /*<<< orphan*/ * peer_cert; } ;
typedef  TYPE_1__ mbedtls_ssl_session ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_1__*,int) ; 

void mbedtls_ssl_session_free( mbedtls_ssl_session *session )
{
    if( session == NULL )
        return;

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    if( session->peer_cert != NULL )
    {
        mbedtls_x509_crt_free( session->peer_cert );
        mbedtls_free( session->peer_cert );
    }
#endif

#if defined(MBEDTLS_SSL_SESSION_TICKETS) && defined(MBEDTLS_SSL_CLI_C)
    mbedtls_free( session->ticket );
#endif

    mbedtls_zeroize( session, sizeof( mbedtls_ssl_session ) );
}