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
typedef  int /*<<< orphan*/  u32 ;
struct tp_mib_stats {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_MIB_INDEX ; 
 int /*<<< orphan*/  A_TP_MIB_RDATA ; 
 int /*<<< orphan*/  t3_read_indirect (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void t3_tp_get_mib_stats(struct adapter *adap, struct tp_mib_stats *tps)
{
	t3_read_indirect(adap, A_TP_MIB_INDEX, A_TP_MIB_RDATA, (u32 *) tps,
			 sizeof(*tps) / sizeof(u32), 0);
}