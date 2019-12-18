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
struct TYPE_3__ {int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/ * get_catalog_object_by_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  get_object_attnum_oid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_objectclass_supported (int /*<<< orphan*/ ) ; 

bool
ObjectExists(const ObjectAddress *address)
{
	if (address == NULL)
	{
		return false;
	}

	if (is_objectclass_supported(address->classId))
	{
		HeapTuple objtup;
		Relation catalog = heap_open(address->classId, AccessShareLock);

#if PG_VERSION_NUM >= 120000
		objtup = get_catalog_object_by_oid(catalog, get_object_attnum_oid(
											   address->classId), address->objectId);
#else
		objtup = get_catalog_object_by_oid(catalog, address->objectId);
#endif
		heap_close(catalog, AccessShareLock);
		if (objtup != NULL)
		{
			return true;
		}

		return false;
	}

	return false;
}