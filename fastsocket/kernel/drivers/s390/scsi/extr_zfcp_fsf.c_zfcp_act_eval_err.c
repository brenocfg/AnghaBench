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
typedef  int u32 ;
typedef  size_t u16 ;
struct zfcp_adapter {TYPE_1__* ccw_device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char const*,size_t) ; 

__attribute__((used)) static void zfcp_act_eval_err(struct zfcp_adapter *adapter, u32 table)
{
	u16 subtable = table >> 16;
	u16 rule = table & 0xffff;
	const char *act_type[] = { "unknown", "OS", "WWPN", "DID", "LUN" };

	if (subtable && subtable < ARRAY_SIZE(act_type))
		dev_warn(&adapter->ccw_device->dev,
			 "Access denied according to ACT rule type %s, "
			 "rule %d\n", act_type[subtable], rule);
}