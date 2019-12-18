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
struct ql3_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPEED_1000 ; 
 scalar_t__ ql_is_fiber (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_phy_get_speed (struct ql3_adapter*) ; 

__attribute__((used)) static u32 ql_get_link_speed(struct ql3_adapter *qdev)
{
	if (ql_is_fiber(qdev))
		return SPEED_1000;
	else
		return ql_phy_get_speed(qdev);
}