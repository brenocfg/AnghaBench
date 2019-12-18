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
typedef  size_t int32 ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 size_t ArrayObjectCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * DeconstructArrayObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static List *
ArrayObjectToCStringList(ArrayType *arrayObject)
{
	List *cstringList = NIL;
	Datum *datumArray = DeconstructArrayObject(arrayObject);
	int32 arraySize = ArrayObjectCount(arrayObject);

	int32 arrayIndex = 0;
	for (arrayIndex = 0; arrayIndex < arraySize; arrayIndex++)
	{
		Datum datum = datumArray[arrayIndex];
		char *cstring = TextDatumGetCString(datum);

		cstringList = lappend(cstringList, cstring);
	}

	Assert(cstringList != NIL);
	return cstringList;
}