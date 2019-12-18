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
 int /*<<< orphan*/  oid_usm ; 
 int /*<<< orphan*/  or_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_usm ; 
 int /*<<< orphan*/  usm_module ; 

__attribute__((used)) static void
usm_start(void)
{
	reg_usm = or_register(&oid_usm,
	    "The MIB module for managing SNMP User-Based Security Model.",
	    usm_module);
}