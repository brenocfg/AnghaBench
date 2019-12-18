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
struct rxrpc_call {int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_rotate_tx_window (struct rxrpc_call*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rxrpc_clear_tx_window(struct rxrpc_call *call)
{
	rxrpc_rotate_tx_window(call, atomic_read(&call->sequence));
}