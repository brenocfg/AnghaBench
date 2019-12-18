#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  phy_poll; } ;
typedef  TYPE_1__ board_info_t ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ TYPE_DM9000E ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void dm9000_schedule_poll(board_info_t *db)
{
	if (db->type == TYPE_DM9000E)
		schedule_delayed_work(&db->phy_poll, HZ * 2);
}