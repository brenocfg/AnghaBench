#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  refobjid; int /*<<< orphan*/  refclassid; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ObjectAddressCollector ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__* Form_pg_depend ;

/* Variables and functions */
 int /*<<< orphan*/  CollectObjectAddress (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ IsObjectAddressOwnedByExtension (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ObjectAddressSet (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ApplyAddToDependencyList(ObjectAddressCollector *collector, Form_pg_depend pg_depend)
{
	ObjectAddress address = { 0 };
	ObjectAddressSet(address, pg_depend->refclassid, pg_depend->refobjid);

	/*
	 * Objects owned by an extension are assumed to be created on the workers by creating
	 * the extension in the cluster, we we don't want explicitly create them.
	 */
	if (IsObjectAddressOwnedByExtension(&address, NULL))
	{
		return;
	}

	CollectObjectAddress(collector, &address);
}