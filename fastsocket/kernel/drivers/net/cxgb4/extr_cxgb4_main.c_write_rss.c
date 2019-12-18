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
typedef  size_t u16 ;
struct TYPE_5__ {size_t abs_id; } ;
struct sge_eth_rxq {TYPE_2__ rspq; } ;
struct port_info {size_t first_qset; int rss_size; int /*<<< orphan*/  viid; TYPE_3__* adapter; } ;
struct TYPE_4__ {struct sge_eth_rxq* ethrxq; } ;
struct TYPE_6__ {int /*<<< orphan*/  fn; TYPE_1__ sge; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (size_t*) ; 
 size_t* kmalloc (int,int /*<<< orphan*/ ) ; 
 int t4_config_rss_range (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t*,int) ; 

__attribute__((used)) static int write_rss(const struct port_info *pi, const u16 *queues)
{
	u16 *rss;
	int i, err;
	const struct sge_eth_rxq *q = &pi->adapter->sge.ethrxq[pi->first_qset];
 
	rss = kmalloc(pi->rss_size * sizeof(u16), GFP_KERNEL);
	if (!rss)
		return -ENOMEM;
 
	/* map the queue indices to queue ids */
	for (i = 0; i < pi->rss_size; i++, queues++)
		rss[i] = q[*queues].rspq.abs_id;
 
	err = t4_config_rss_range(pi->adapter, pi->adapter->fn, pi->viid, 0,
				  pi->rss_size, rss, pi->rss_size);
	kfree(rss);
	return err;
}