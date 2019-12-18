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
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int /*<<< orphan*/  DatumGetObjectId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enum_in ; 

__attribute__((used)) static Oid
LookupEnumValueId(Oid typeId, char *valueName)
{
	Datum typeIdDatum = ObjectIdGetDatum(typeId);
	Datum valueDatum = CStringGetDatum(valueName);
	Datum valueIdDatum = DirectFunctionCall2(enum_in, valueDatum, typeIdDatum);
	Oid valueId = DatumGetObjectId(valueIdDatum);

	return valueId;
}