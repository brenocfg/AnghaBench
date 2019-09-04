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
 int /*<<< orphan*/ * GetElement (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStrValue (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  StrCpy (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_STR ; 

bool PackGetStrEx(PACK *p, char *name, char *str, UINT size, UINT index)
{
	ELEMENT *e;
	// Validate arguments
	if (p == NULL || name == NULL || str == NULL || size == 0)
	{
		return false;
	}

	str[0] = 0;

	e = GetElement(p, name, VALUE_STR);
	if (e == NULL)
	{
		return false;
	}

	StrCpy(str, size, GetStrValue(e, index));
	return true;
}