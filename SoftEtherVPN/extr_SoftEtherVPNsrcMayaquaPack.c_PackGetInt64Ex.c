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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/ * GetElement (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetInt64Value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_INT64 ; 

UINT64 PackGetInt64Ex(PACK *p, char *name, UINT index)
{
	ELEMENT *e;
	// Validate arguments
	if (p == NULL || name == NULL)
	{
		return 0;
	}

	e = GetElement(p, name, VALUE_INT64);
	if (e == NULL)
	{
		return 0;
	}
	return GetInt64Value(e, index);
}