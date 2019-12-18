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
 scalar_t__ InvalidOid ; 
 scalar_t__ LookupEnumValueId (scalar_t__,char*) ; 
 scalar_t__ LookupTypeOid (char*) ; 

__attribute__((used)) static Oid
LookupStringEnumValueId(char *enumName, char *valueName)
{
	Oid enumTypeId = LookupTypeOid(enumName);

	if (enumTypeId == InvalidOid)
	{
		return InvalidOid;
	}
	else
	{
		Oid valueId = LookupEnumValueId(enumTypeId, valueName);
		return valueId;
	}
}