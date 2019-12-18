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
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ mbedtls_net_context ;

/* Variables and functions */
#define  EAGAIN 129 
#define  EWOULDBLOCK 128 
 int /*<<< orphan*/  F_GETFL ; 
 int O_NONBLOCK ; 
 int errno ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_would_block( const mbedtls_net_context *ctx )
{
    /*
     * Never return 'WOULD BLOCK' on a non-blocking socket
     */
    if( ( fcntl( ctx->fd, F_GETFL ) & O_NONBLOCK ) != O_NONBLOCK )
        return( 0 );

    switch( errno )
    {
#if defined EAGAIN
        case EAGAIN:
#endif
#if defined EWOULDBLOCK && EWOULDBLOCK != EAGAIN
        case EWOULDBLOCK:
#endif
            return( 1 );
    }
    return( 0 );
}