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
 int /*<<< orphan*/  oid_vacm ; 
 int /*<<< orphan*/  or_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_vacm ; 
 int /*<<< orphan*/  vacm_add_context (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vacm_module ; 

__attribute__((used)) static void
vacm_start(void)
{
	static char dflt_ctx[] = "";

	reg_vacm = or_register(&oid_vacm,
	    "The MIB module for managing SNMP View-based Access Control Model.",
	    vacm_module);

	(void)vacm_add_context(dflt_ctx, reg_vacm);
}