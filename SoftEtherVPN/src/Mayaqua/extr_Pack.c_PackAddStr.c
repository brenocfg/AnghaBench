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
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  ELEMENT ;

/* Variables and functions */
 int AddElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewElement (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * NewStrValue (char*) ; 
 int /*<<< orphan*/  VALUE_STR ; 

ELEMENT *PackAddStr(PACK *p, char *name, char *str)
{
	VALUE *v;
	ELEMENT *e = NULL;
	// Validate arguments
	if (p == NULL || name == NULL || str == NULL)
	{
		return NULL;
	}

	v = NewStrValue(str);
	e = NewElement(name, VALUE_STR, 1, &v);
	if (AddElement(p, e) == false)
	{
		return NULL;
	}
	return e;
}