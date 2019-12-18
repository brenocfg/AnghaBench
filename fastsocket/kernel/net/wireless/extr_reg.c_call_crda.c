#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  is_world_regdom (char*) ; 
 int kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 TYPE_2__* reg_pdev ; 
 int /*<<< orphan*/  reg_regdb_query (char const*) ; 

__attribute__((used)) static int call_crda(const char *alpha2)
{
	if (!is_world_regdom((char *) alpha2))
		pr_info("Calling CRDA for country: %c%c\n",
			alpha2[0], alpha2[1]);
	else
		pr_info("Calling CRDA to update world regulatory domain\n");

	/* query internal regulatory database (if it exists) */
	reg_regdb_query(alpha2);

	return kobject_uevent(&reg_pdev->dev.kobj, KOBJ_CHANGE);
}