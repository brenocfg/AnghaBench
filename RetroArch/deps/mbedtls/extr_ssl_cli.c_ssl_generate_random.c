#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int mbedtls_time_t ;
struct TYPE_7__ {TYPE_2__* conf; TYPE_1__* handshake; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_6__ {scalar_t__ transport; int (* f_rng ) (int /*<<< orphan*/ ,unsigned char*,int) ;int /*<<< orphan*/  p_rng; } ;
struct TYPE_5__ {unsigned char* randbytes; int /*<<< orphan*/ * verify_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 scalar_t__ MBEDTLS_SSL_TRANSPORT_DATAGRAM ; 
 int mbedtls_time (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int ssl_generate_random( mbedtls_ssl_context *ssl )
{
    int ret;
    unsigned char *p = ssl->handshake->randbytes;
#if defined(MBEDTLS_HAVE_TIME)
    mbedtls_time_t t;
#endif

    /*
     * When responding to a verify request, MUST reuse random (RFC 6347 4.2.1)
     */
#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ssl->handshake->verify_cookie != NULL )
    {
        return( 0 );
    }
#endif

#if defined(MBEDTLS_HAVE_TIME)
    t = mbedtls_time( NULL );
    *p++ = (unsigned char)( t >> 24 );
    *p++ = (unsigned char)( t >> 16 );
    *p++ = (unsigned char)( t >>  8 );
    *p++ = (unsigned char)( t       );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello, current time: %lu", t ) );
#else
    if( ( ret = ssl->conf->f_rng( ssl->conf->p_rng, p, 4 ) ) != 0 )
        return( ret );

    p += 4;
#endif /* MBEDTLS_HAVE_TIME */

    if( ( ret = ssl->conf->f_rng( ssl->conf->p_rng, p, 28 ) ) != 0 )
        return( ret );

    return( 0 );
}