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
struct rpc_xprt {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_CLOSE_WAIT ; 
 int /*<<< orphan*/  XPRT_CLOSING ; 
 int /*<<< orphan*/  XPRT_CONNECTION_ABORT ; 
 int /*<<< orphan*/  XPRT_CONNECTION_CLOSE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  smp_mb__before_clear_bit () ; 

__attribute__((used)) static void xs_sock_reset_connection_flags(struct rpc_xprt *xprt)
{
	smp_mb__before_clear_bit();
	clear_bit(XPRT_CONNECTION_ABORT, &xprt->state);
	clear_bit(XPRT_CONNECTION_CLOSE, &xprt->state);
	clear_bit(XPRT_CLOSE_WAIT, &xprt->state);
	clear_bit(XPRT_CLOSING, &xprt->state);
	smp_mb__after_clear_bit();
}