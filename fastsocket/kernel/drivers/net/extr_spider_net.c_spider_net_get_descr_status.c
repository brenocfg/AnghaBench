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
struct spider_net_hw_descr {int dmac_cmd_status; } ;

/* Variables and functions */
 int SPIDER_NET_DESCR_IND_PROC_MASK ; 

__attribute__((used)) static inline int
spider_net_get_descr_status(struct spider_net_hw_descr *hwdescr)
{
	return hwdescr->dmac_cmd_status & SPIDER_NET_DESCR_IND_PROC_MASK;
}