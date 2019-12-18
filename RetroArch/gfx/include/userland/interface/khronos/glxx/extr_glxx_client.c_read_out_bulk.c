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
typedef  int /*<<< orphan*/  RPC_RECV_FLAG_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int RPC_RECV_FLAG_BULK ; 
 int RPC_RECV_FLAG_LEN ; 
 int /*<<< orphan*/  rpc_recv (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_out_bulk(CLIENT_THREAD_STATE_T *thread, void *out)
{
   rpc_recv(thread, out, NULL, (RPC_RECV_FLAG_T)(RPC_RECV_FLAG_BULK | RPC_RECV_FLAG_LEN));
}