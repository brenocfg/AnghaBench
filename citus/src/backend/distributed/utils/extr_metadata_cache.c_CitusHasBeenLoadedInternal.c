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
 scalar_t__ CurrentExtensionObject ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ IsBinaryUpgrade ; 
 scalar_t__ creating_extension ; 
 scalar_t__ get_extension_oid (char*,int) ; 

__attribute__((used)) static bool
CitusHasBeenLoadedInternal(void)
{
	Oid citusExtensionOid = InvalidOid;

	if (IsBinaryUpgrade)
	{
		/* never use Citus logic during pg_upgrade */
		return false;
	}

	citusExtensionOid = get_extension_oid("citus", true);
	if (citusExtensionOid == InvalidOid)
	{
		/* Citus extension does not exist yet */
		return false;
	}

	if (creating_extension && CurrentExtensionObject == citusExtensionOid)
	{
		/*
		 * We do not use Citus hooks during CREATE/ALTER EXTENSION citus
		 * since the objects used by the C code might be not be there yet.
		 */
		return false;
	}

	/* citus extension exists and has been created */
	return true;
}