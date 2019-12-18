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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ rsp; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 *qlcnic_83xx_copy_stats(struct qlcnic_cmd_args *cmd,
					  u64 *data, int index)
{
	u32 low, hi;
	u64 val;

	low = cmd->rsp.arg[index];
	hi = cmd->rsp.arg[index + 1];
	val = (((u64) low) | (((u64) hi) << 32));
	*data++ = val;
	return data;
}