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
typedef  int u_long ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ mbedtls_net_context ;

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_NBIO ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int ioctlsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int mbedtls_net_set_nonblock( mbedtls_net_context *ctx )
{
#if defined(__CELLOS_LV2__) || defined(VITA) || defined(WIIU)
   int i = 1;
   setsockopt(ctx->fd, SOL_SOCKET, SO_NBIO, &i, sizeof(int));
   return 1;
#elif ( defined(_WIN32) || defined(_WIN32_WCE) ) && !defined(EFIX64) && \
    !defined(EFI32)
    u_long n = 1;
    return( ioctlsocket( ctx->fd, FIONBIO, &n ) );
#else
    return( fcntl( ctx->fd, F_SETFL, fcntl( ctx->fd, F_GETFL ) | O_NONBLOCK ) );
#endif
}