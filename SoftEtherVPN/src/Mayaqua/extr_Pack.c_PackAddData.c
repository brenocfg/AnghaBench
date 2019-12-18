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
typedef  int /*<<< orphan*/  VALUE ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  ELEMENT ;

/* Variables and functions */
 int AddElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewDataValue (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewElement (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  VALUE_DATA ; 

ELEMENT *PackAddData(PACK *p, char *name, void *data, UINT size)
{
	VALUE *v;
	ELEMENT *e;
	// Validate arguments
	if (p == NULL || data == NULL || name == NULL)
	{
		return NULL;
	}

	v = NewDataValue(data, size);
	e = NewElement(name, VALUE_DATA, 1, &v);
	if (AddElement(p, e) == false)
	{
		return NULL;
	}

	return e;
}