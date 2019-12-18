#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ tcpOutRsts; scalar_t__ tcpRetransSegs; scalar_t__ tcpOutSegs; scalar_t__ tcpInSegs; } ;
union rdma_protocol_stats {TYPE_3__ iw; } ;
struct tp_tcp_stats {scalar_t__ tcpOutSegs; scalar_t__ tcpOutRsts; scalar_t__ tcpRetransSegs; scalar_t__ tcpInSegs; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_5__ {TYPE_1__ lldi; } ;
struct c4iw_dev {TYPE_2__ rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgb4_get_tcp_stats (int /*<<< orphan*/ ,struct tp_tcp_stats*,struct tp_tcp_stats*) ; 
 int /*<<< orphan*/  memset (union rdma_protocol_stats*,int /*<<< orphan*/ ,int) ; 
 struct c4iw_dev* to_c4iw_dev (struct ib_device*) ; 

__attribute__((used)) static int c4iw_get_mib(struct ib_device *ibdev,
			union rdma_protocol_stats *stats)
{
	struct tp_tcp_stats v4, v6;
	struct c4iw_dev *c4iw_dev = to_c4iw_dev(ibdev);

	cxgb4_get_tcp_stats(c4iw_dev->rdev.lldi.pdev, &v4, &v6);
	memset(stats, 0, sizeof *stats);
	stats->iw.tcpInSegs = v4.tcpInSegs + v6.tcpInSegs;
	stats->iw.tcpOutSegs = v4.tcpOutSegs + v6.tcpOutSegs;
	stats->iw.tcpRetransSegs = v4.tcpRetransSegs + v6.tcpRetransSegs;
	stats->iw.tcpOutRsts = v4.tcpOutRsts + v6.tcpOutSegs;

	return 0;
}