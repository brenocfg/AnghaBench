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
struct TYPE_2__ {scalar_t__ distLocalGroupRelationId; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ InvalidOid ; 
 int LocalGroupId ; 
 TYPE_1__ MetadataCache ; 

__attribute__((used)) static void
InvalidateLocalGroupIdRelationCacheCallback(Datum argument, Oid relationId)
{
	/* when invalidation happens simply set the LocalGroupId to the default value */
	if (relationId == InvalidOid || relationId == MetadataCache.distLocalGroupRelationId)
	{
		LocalGroupId = -1;
	}
}