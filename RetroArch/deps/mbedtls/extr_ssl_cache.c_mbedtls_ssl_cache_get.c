#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_x509_crt ;
typedef  scalar_t__ mbedtls_time_t ;
struct TYPE_9__ {scalar_t__ ciphersuite; scalar_t__ compression; scalar_t__ id_len; int /*<<< orphan*/ * peer_cert; int /*<<< orphan*/  verify_result; int /*<<< orphan*/  master; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ mbedtls_ssl_session ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * p; } ;
struct TYPE_7__ {scalar_t__ ciphersuite; scalar_t__ compression; scalar_t__ id_len; int /*<<< orphan*/  verify_result; int /*<<< orphan*/  master; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_2__ peer_cert; TYPE_1__ session; scalar_t__ timestamp; struct TYPE_10__* next; } ;
typedef  TYPE_4__ mbedtls_ssl_cache_entry ;
struct TYPE_11__ {int timeout; int /*<<< orphan*/  mutex; TYPE_4__* chain; } ;
typedef  TYPE_5__ mbedtls_ssl_cache_context ;

/* Variables and functions */
 int /*<<< orphan*/ * mbedtls_calloc (int,int) ; 
 int /*<<< orphan*/  mbedtls_free (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_x509_crt_init (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_x509_crt_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mbedtls_ssl_cache_get( void *data, mbedtls_ssl_session *session )
{
    int ret = 1;
#if defined(MBEDTLS_HAVE_TIME)
    mbedtls_time_t t = mbedtls_time( NULL );
#endif
    mbedtls_ssl_cache_context *cache = (mbedtls_ssl_cache_context *) data;
    mbedtls_ssl_cache_entry *cur, *entry;

#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_lock( &cache->mutex ) != 0 )
        return( 1 );
#endif

    cur = cache->chain;
    entry = NULL;

    while( cur != NULL )
    {
        entry = cur;
        cur = cur->next;

#if defined(MBEDTLS_HAVE_TIME)
        if( cache->timeout != 0 &&
            (int) ( t - entry->timestamp ) > cache->timeout )
            continue;
#endif

        if( session->ciphersuite != entry->session.ciphersuite ||
            session->compression != entry->session.compression ||
            session->id_len != entry->session.id_len )
            continue;

        if( memcmp( session->id, entry->session.id,
                    entry->session.id_len ) != 0 )
            continue;

        memcpy( session->master, entry->session.master, 48 );

        session->verify_result = entry->session.verify_result;

#if defined(MBEDTLS_X509_CRT_PARSE_C)
        /*
         * Restore peer certificate (without rest of the original chain)
         */
        if( entry->peer_cert.p != NULL )
        {
            if( ( session->peer_cert = mbedtls_calloc( 1,
                                 sizeof(mbedtls_x509_crt) ) ) == NULL )
            {
                ret = 1;
                goto exit;
            }

            mbedtls_x509_crt_init( session->peer_cert );
            if( mbedtls_x509_crt_parse( session->peer_cert, entry->peer_cert.p,
                                entry->peer_cert.len ) != 0 )
            {
                mbedtls_free( session->peer_cert );
                session->peer_cert = NULL;
                ret = 1;
                goto exit;
            }
        }
#endif /* MBEDTLS_X509_CRT_PARSE_C */

        ret = 0;
        goto exit;
    }

exit:
#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_unlock( &cache->mutex ) != 0 )
        ret = 1;
#endif

    return( ret );
}