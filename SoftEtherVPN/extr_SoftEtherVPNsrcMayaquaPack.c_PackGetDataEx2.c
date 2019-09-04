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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GetDataValue (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ GetDataValueSize (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * GetElement (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_DATA ; 

bool PackGetDataEx2(PACK *p, char *name, void *data, UINT size, UINT index)
{
	ELEMENT *e;
	// Validate arguments
	if (p == NULL || name == NULL)
	{
		return false;
	}

	e = GetElement(p, name, VALUE_DATA);
	if (e == NULL)
	{
		return false;
	}
	if (GetDataValueSize(e, index) != size)
	{
		return false;
	}
	Copy(data, GetDataValue(e, index), GetDataValueSize(e, index));
	return true;
}