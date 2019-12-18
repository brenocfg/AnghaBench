#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bad_reply_count; int /*<<< orphan*/  failed_marshal_count; int /*<<< orphan*/  hardway_register_count; int /*<<< orphan*/  fixup_copy_count; int /*<<< orphan*/  pullup_copy_count; int /*<<< orphan*/  total_rdma_reply; int /*<<< orphan*/  total_rdma_request; int /*<<< orphan*/  reply_chunk_count; int /*<<< orphan*/  write_chunk_count; int /*<<< orphan*/  read_chunk_count; } ;
struct rpcrdma_xprt {TYPE_2__ rx_stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  bklog_u; int /*<<< orphan*/  req_u; int /*<<< orphan*/  bad_xids; int /*<<< orphan*/  recvs; int /*<<< orphan*/  sends; int /*<<< orphan*/  connect_time; int /*<<< orphan*/  connect_count; int /*<<< orphan*/  bind_count; } ;
struct rpc_xprt {TYPE_1__ stat; scalar_t__ last_used; } ;

/* Variables and functions */
 long HZ ; 
 scalar_t__ jiffies ; 
 struct rpcrdma_xprt* rpcx_to_rdmax (struct rpc_xprt*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xprt_connected (struct rpc_xprt*) ; 

__attribute__((used)) static void xprt_rdma_print_stats(struct rpc_xprt *xprt, struct seq_file *seq)
{
	struct rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	long idle_time = 0;

	if (xprt_connected(xprt))
		idle_time = (long)(jiffies - xprt->last_used) / HZ;

	seq_printf(seq,
	  "\txprt:\trdma %u %lu %lu %lu %ld %lu %lu %lu %Lu %Lu "
	  "%lu %lu %lu %Lu %Lu %Lu %Lu %lu %lu %lu\n",

	   0,	/* need a local port? */
	   xprt->stat.bind_count,
	   xprt->stat.connect_count,
	   xprt->stat.connect_time,
	   idle_time,
	   xprt->stat.sends,
	   xprt->stat.recvs,
	   xprt->stat.bad_xids,
	   xprt->stat.req_u,
	   xprt->stat.bklog_u,

	   r_xprt->rx_stats.read_chunk_count,
	   r_xprt->rx_stats.write_chunk_count,
	   r_xprt->rx_stats.reply_chunk_count,
	   r_xprt->rx_stats.total_rdma_request,
	   r_xprt->rx_stats.total_rdma_reply,
	   r_xprt->rx_stats.pullup_copy_count,
	   r_xprt->rx_stats.fixup_copy_count,
	   r_xprt->rx_stats.hardway_register_count,
	   r_xprt->rx_stats.failed_marshal_count,
	   r_xprt->rx_stats.bad_reply_count);
}