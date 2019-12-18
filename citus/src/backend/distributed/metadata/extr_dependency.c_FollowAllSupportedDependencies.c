#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ deptype; int /*<<< orphan*/  refobjid; int /*<<< orphan*/  refclassid; } ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ObjectAddressCollector ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__* Form_pg_depend ;

/* Variables and functions */
 scalar_t__ CitusExtensionObject (TYPE_1__*) ; 
 scalar_t__ DEPENDENCY_EXTENSION ; 
 scalar_t__ DEPENDENCY_NORMAL ; 
 scalar_t__ IsObjectAddressCollected (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsObjectAddressOwnedByExtension (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ObjectAddressSet (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SupportedDependencyByCitus (TYPE_1__*) ; 

__attribute__((used)) static bool
FollowAllSupportedDependencies(ObjectAddressCollector *collector, Form_pg_depend
							   pg_depend)
{
	ObjectAddress address = { 0 };
	ObjectAddressSet(address, pg_depend->refclassid, pg_depend->refobjid);

	/*
	 *  Follow only normal and extension dependencies. The latter is used to reach the
	 *  extensions, the objects that directly depend on the extension are eliminated
	 *  during the "apply" phase.
	 *
	 *  Other dependencies are internal dependencies and managed by postgres.
	 */
	if (pg_depend->deptype != DEPENDENCY_NORMAL &&
		pg_depend->deptype != DEPENDENCY_EXTENSION)
	{
		return false;
	}

	/*
	 * If the object is already in our dependency list we do not have to follow any
	 * further
	 */
	if (IsObjectAddressCollected(&address, collector))
	{
		return false;
	}

	/*
	 * We can only distribute dependencies that citus knows how to distribute.
	 *
	 * But we don't want to bail out if the object is owned by extension, because
	 * Citus can create the extension.
	 */
	if (!SupportedDependencyByCitus(&address) &&
		!IsObjectAddressOwnedByExtension(&address, NULL))
	{
		return false;
	}

	if (CitusExtensionObject(&address))
	{
		/* following citus extension could complicate role management */
		return false;
	}

	return true;
}