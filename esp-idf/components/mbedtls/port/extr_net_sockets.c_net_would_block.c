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
typedef  int /*<<< orphan*/  mbedtls_net_context ;

/* Variables and functions */
#define  EAGAIN 129 
#define  EWOULDBLOCK 128 
 int errno ; 

__attribute__((used)) static int net_would_block( const mbedtls_net_context *ctx )
{
    int error = errno;

    switch ( errno = error ) {
#if defined EAGAIN
    case EAGAIN:
#endif
#if defined EWOULDBLOCK && EWOULDBLOCK != EAGAIN
    case EWOULDBLOCK:
#endif
        return ( 1 );
    }
    return ( 0 );
}