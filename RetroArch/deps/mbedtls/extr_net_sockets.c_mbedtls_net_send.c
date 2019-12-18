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
struct TYPE_3__ {int fd; } ;
typedef  TYPE_1__ mbedtls_net_context ;

/* Variables and functions */
 scalar_t__ ECONNRESET ; 
 scalar_t__ EINTR ; 
 scalar_t__ EPIPE ; 
 int MBEDTLS_ERR_NET_CONN_RESET ; 
 int MBEDTLS_ERR_NET_INVALID_CONTEXT ; 
 int MBEDTLS_ERR_NET_SEND_FAILED ; 
 int MBEDTLS_ERR_SSL_WANT_WRITE ; 
 scalar_t__ WSAECONNRESET ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ errno ; 
 scalar_t__ net_would_block (TYPE_1__ const*) ; 
 scalar_t__ write (int,unsigned char const*,size_t) ; 

int mbedtls_net_send( void *ctx, const unsigned char *buf, size_t len )
{
    int ret;
    int fd = ((mbedtls_net_context *) ctx)->fd;

    if( fd < 0 )
        return( MBEDTLS_ERR_NET_INVALID_CONTEXT );

    ret = (int) write( fd, buf, len );

    if( ret < 0 )
    {
        if( net_would_block((const mbedtls_net_context*)ctx) != 0 )
            return( MBEDTLS_ERR_SSL_WANT_WRITE );

#if ( defined(_WIN32) || defined(_WIN32_WCE) ) && !defined(EFIX64) && \
    !defined(EFI32)
        if( WSAGetLastError() == WSAECONNRESET )
            return( MBEDTLS_ERR_NET_CONN_RESET );
#else
        if( errno == EPIPE || errno == ECONNRESET )
            return( MBEDTLS_ERR_NET_CONN_RESET );

        if( errno == EINTR )
            return( MBEDTLS_ERR_SSL_WANT_WRITE );
#endif

        return( MBEDTLS_ERR_NET_SEND_FAILED );
    }

    return( ret );
}