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

/* Variables and functions */
 int /*<<< orphan*/  oid_notification ; 
 int /*<<< orphan*/  oid_target ; 
 void* or_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* reg_notification ; 
 void* reg_target ; 
 int /*<<< orphan*/  target_module ; 

__attribute__((used)) static void
target_start(void)
{
	reg_target = or_register(&oid_target,
	    "The MIB module for managing SNMP Management Targets.",
	    target_module);
	reg_notification = or_register(&oid_notification,
	    "The MIB module for configuring generation of SNMP notifications.",
	    target_module);
}