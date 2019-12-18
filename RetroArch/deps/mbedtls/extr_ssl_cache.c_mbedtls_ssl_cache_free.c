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
struct TYPE_6__ {TYPE_2__* p; } ;
struct TYPE_7__ {TYPE_1__ peer_cert; int /*<<< orphan*/  session; struct TYPE_7__* next; } ;
typedef  TYPE_2__ mbedtls_ssl_cache_entry ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; TYPE_2__* chain; } ;
typedef  TYPE_3__ mbedtls_ssl_cache_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_mutex_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ssl_session_free (int /*<<< orphan*/ *) ; 

void mbedtls_ssl_cache_free( mbedtls_ssl_cache_context *cache )
{
    mbedtls_ssl_cache_entry *cur, *prv;

    cur = cache->chain;

    while( cur != NULL )
    {
        prv = cur;
        cur = cur->next;

        mbedtls_ssl_session_free( &prv->session );

#if defined(MBEDTLS_X509_CRT_PARSE_C)
        mbedtls_free( prv->peer_cert.p );
#endif /* MBEDTLS_X509_CRT_PARSE_C */

        mbedtls_free( prv );
    }

#if defined(MBEDTLS_THREADING_C)
    mbedtls_mutex_free( &cache->mutex );
#endif
}