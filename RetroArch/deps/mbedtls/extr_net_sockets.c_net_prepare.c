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
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int /*<<< orphan*/ ) ; 
 int MBEDTLS_ERR_NET_SOCKET_FAILED ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wsa_init_done ; 

__attribute__((used)) static int net_prepare( void )
{
#if ( defined(_WIN32) || defined(_WIN32_WCE) ) && !defined(EFIX64) && \
    !defined(EFI32)
    WSADATA wsaData;

    if( wsa_init_done == 0 )
    {
        if( WSAStartup( MAKEWORD(2,0), &wsaData ) != 0 )
            return( MBEDTLS_ERR_NET_SOCKET_FAILED );

        wsa_init_done = 1;
    }
#else
#if !defined(EFIX64) && !defined(EFI32)
    signal( SIGPIPE, SIG_IGN );
#endif
#endif
    return( 0 );
}