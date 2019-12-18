#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
typedef  void* u_long ;
struct TYPE_2__ {void* cb_proc; void* cb_vers; void* cb_prog; int /*<<< orphan*/  cb_rpcvers; } ;
struct rpc_msg {TYPE_1__ rm_call; int /*<<< orphan*/  rm_direction; scalar_t__ rm_xid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL ; 
 int /*<<< orphan*/  RPC_MSG_VERSION ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
rpc_msg_init(struct rpc_msg *mp, u_long prog, u_long vers, u_long proc)
{
  /*
   * Initialize the message
   */
  memset((voidp) mp, 0, sizeof(*mp));
  mp->rm_xid = 0;
  mp->rm_direction = CALL;
  mp->rm_call.cb_rpcvers = RPC_MSG_VERSION;
  mp->rm_call.cb_prog = prog;
  mp->rm_call.cb_vers = vers;
  mp->rm_call.cb_proc = proc;
}