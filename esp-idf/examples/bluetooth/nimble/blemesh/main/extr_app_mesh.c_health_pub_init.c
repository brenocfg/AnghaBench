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
struct TYPE_2__ {int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MESH_HEALTH_FAULT_MSG (int /*<<< orphan*/ ) ; 
 TYPE_1__ health_pub ; 

__attribute__((used)) static void
health_pub_init(void)
{
    health_pub.msg  = BT_MESH_HEALTH_FAULT_MSG(0);
}