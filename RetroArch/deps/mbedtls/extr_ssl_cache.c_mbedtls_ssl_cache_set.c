#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_x509_buf ;
typedef  scalar_t__ mbedtls_time_t ;
struct TYPE_13__ {TYPE_2__* peer_cert; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ mbedtls_ssl_session ;
struct TYPE_17__ {int /*<<< orphan*/ * peer_cert; int /*<<< orphan*/  id_len; int /*<<< orphan*/  id; } ;
struct TYPE_16__ {int len; TYPE_7__* p; } ;
struct TYPE_14__ {scalar_t__ timestamp; TYPE_7__ session; TYPE_6__ peer_cert; struct TYPE_14__* next; } ;
typedef  TYPE_4__ mbedtls_ssl_cache_entry ;
struct TYPE_15__ {int timeout; int max_entries; int /*<<< orphan*/  mutex; TYPE_4__* chain; } ;
typedef  TYPE_5__ mbedtls_ssl_cache_context ;
struct TYPE_11__ {int len; TYPE_3__ const* p; } ;
struct TYPE_12__ {TYPE_1__ raw; } ;

/* Variables and functions */
 void* mbedtls_calloc (int,int) ; 
 int /*<<< orphan*/  mbedtls_free (TYPE_7__*) ; 
 int mbedtls_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_7__*,TYPE_3__ const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int mbedtls_ssl_cache_set( void *data, const mbedtls_ssl_session *session )
{
    int ret = 1;
#if defined(MBEDTLS_HAVE_TIME)
    mbedtls_time_t t = time( NULL ), oldest = 0;
    mbedtls_ssl_cache_entry *old = NULL;
#endif
    mbedtls_ssl_cache_context *cache = (mbedtls_ssl_cache_context *) data;
    mbedtls_ssl_cache_entry *cur, *prv;
    int count = 0;

#if defined(MBEDTLS_THREADING_C)
    if( ( ret = mbedtls_mutex_lock( &cache->mutex ) ) != 0 )
        return( ret );
#endif

    cur = cache->chain;
    prv = NULL;

    while( cur != NULL )
    {
        count++;

#if defined(MBEDTLS_HAVE_TIME)
        if( cache->timeout != 0 &&
            (int) ( t - cur->timestamp ) > cache->timeout )
        {
            cur->timestamp = t;
            break; /* expired, reuse this slot, update timestamp */
        }
#endif

        if( memcmp( session->id, cur->session.id, cur->session.id_len ) == 0 )
            break; /* client reconnected, keep timestamp for session id */

#if defined(MBEDTLS_HAVE_TIME)
        if( oldest == 0 || cur->timestamp < oldest )
        {
            oldest = cur->timestamp;
            old = cur;
        }
#endif

        prv = cur;
        cur = cur->next;
    }

    if( cur == NULL )
    {
#if defined(MBEDTLS_HAVE_TIME)
        /*
         * Reuse oldest entry if max_entries reached
         */
        if( count >= cache->max_entries )
        {
            if( old == NULL )
            {
                ret = 1;
                goto exit;
            }

            cur = old;
        }
#else /* MBEDTLS_HAVE_TIME */
        /*
         * Reuse first entry in chain if max_entries reached,
         * but move to last place
         */
        if( count >= cache->max_entries )
        {
            if( cache->chain == NULL )
            {
                ret = 1;
                goto exit;
            }

            cur = cache->chain;
            cache->chain = cur->next;
            cur->next = NULL;
            prv->next = cur;
        }
#endif /* MBEDTLS_HAVE_TIME */
        else
        {
            /*
             * max_entries not reached, create new entry
             */
            cur = mbedtls_calloc( 1, sizeof(mbedtls_ssl_cache_entry) );
            if( cur == NULL )
            {
                ret = 1;
                goto exit;
            }

            if( prv == NULL )
                cache->chain = cur;
            else
                prv->next = cur;
        }

#if defined(MBEDTLS_HAVE_TIME)
        cur->timestamp = t;
#endif
    }

    memcpy( &cur->session, session, sizeof( mbedtls_ssl_session ) );

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    /*
     * If we're reusing an entry, free its certificate first
     */
    if( cur->peer_cert.p != NULL )
    {
        mbedtls_free( cur->peer_cert.p );
        memset( &cur->peer_cert, 0, sizeof(mbedtls_x509_buf) );
    }

    /*
     * Store peer certificate
     */
    if( session->peer_cert != NULL )
    {
        cur->peer_cert.p = mbedtls_calloc( 1, session->peer_cert->raw.len );
        if( cur->peer_cert.p == NULL )
        {
            ret = 1;
            goto exit;
        }

        memcpy( cur->peer_cert.p, session->peer_cert->raw.p,
                session->peer_cert->raw.len );
        cur->peer_cert.len = session->peer_cert->raw.len;

        cur->session.peer_cert = NULL;
    }
#endif /* MBEDTLS_X509_CRT_PARSE_C */

    ret = 0;

exit:
#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_unlock( &cache->mutex ) != 0 )
        ret = 1;
#endif

    return( ret );
}