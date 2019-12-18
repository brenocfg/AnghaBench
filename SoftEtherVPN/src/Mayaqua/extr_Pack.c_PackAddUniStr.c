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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  VALUE ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  ELEMENT ;

/* Variables and functions */
 int AddElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewElement (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * NewUniStrValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VALUE_UNISTR ; 

ELEMENT *PackAddUniStr(PACK *p, char *name, wchar_t *unistr)
{
	VALUE *v;
	ELEMENT *e = NULL;
	// Validate arguments
	if (p == NULL || name == NULL || unistr == NULL)
	{
		return NULL;
	}

	v = NewUniStrValue(unistr);
	e = NewElement(name, VALUE_UNISTR, 1, &v);
	if (AddElement(p, e) == false)
	{
		return NULL;
	}
	return e;
}