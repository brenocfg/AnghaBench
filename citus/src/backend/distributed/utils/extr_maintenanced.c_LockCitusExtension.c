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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  ExtensionRelationId ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  LockDatabaseObject (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_extension_oid (char*,int) ; 

__attribute__((used)) static bool
LockCitusExtension(void)
{
	Oid recheckExtensionOid = InvalidOid;

	Oid extensionOid = get_extension_oid("citus", true);
	if (extensionOid == InvalidOid)
	{
		/* citus extension does not exist */
		return false;
	}

	LockDatabaseObject(ExtensionRelationId, extensionOid, 0, AccessShareLock);

	/*
	 * The extension may have been dropped and possibly recreated prior to
	 * obtaining a lock. Check whether we still get the expected OID.
	 */
	recheckExtensionOid = get_extension_oid("citus", true);
	if (recheckExtensionOid != extensionOid)
	{
		return false;
	}

	return true;
}