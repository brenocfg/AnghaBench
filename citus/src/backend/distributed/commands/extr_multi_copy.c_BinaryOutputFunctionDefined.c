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
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  IOFunc_send ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_type_io_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
BinaryOutputFunctionDefined(Oid typeId)
{
	Oid typeFunctionId = InvalidOid;
	Oid typeIoParam = InvalidOid;
	int16 typeLength = 0;
	bool typeByVal = false;
	char typeAlign = 0;
	char typeDelim = 0;

	get_type_io_data(typeId, IOFunc_send, &typeLength, &typeByVal,
					 &typeAlign, &typeDelim, &typeIoParam, &typeFunctionId);

	if (OidIsValid(typeFunctionId))
	{
		return true;
	}

	return false;
}