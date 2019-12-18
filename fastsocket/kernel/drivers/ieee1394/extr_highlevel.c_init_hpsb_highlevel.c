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
typedef  int u64 ;
struct TYPE_4__ {int start; int end; int /*<<< orphan*/  host_list; int /*<<< orphan*/ * op; int /*<<< orphan*/  hl_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_list; scalar_t__ end; scalar_t__ start; int /*<<< orphan*/ * op; int /*<<< orphan*/  hl_list; } ;
struct hpsb_host {int /*<<< orphan*/  addr_space; TYPE_2__ dummy_max_addr; TYPE_1__ dummy_zero_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dummy_ops ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_hpsb_highlevel(struct hpsb_host *host)
{
	INIT_LIST_HEAD(&host->dummy_zero_addr.host_list);
	INIT_LIST_HEAD(&host->dummy_zero_addr.hl_list);
	INIT_LIST_HEAD(&host->dummy_max_addr.host_list);
	INIT_LIST_HEAD(&host->dummy_max_addr.hl_list);

	host->dummy_zero_addr.op = host->dummy_max_addr.op = &dummy_ops;

	host->dummy_zero_addr.start = host->dummy_zero_addr.end = 0;
	host->dummy_max_addr.start = host->dummy_max_addr.end = ((u64) 1) << 48;

	list_add_tail(&host->dummy_zero_addr.host_list, &host->addr_space);
	list_add_tail(&host->dummy_max_addr.host_list, &host->addr_space);
}