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

/* Variables and functions */
 int /*<<< orphan*/  AddElement (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewElement (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * NewUniStrValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VALUE_UNISTR ; 

void PackAddUniStr(PACK *p, char *name, wchar_t *unistr)
{
	VALUE *v;
	// Validate arguments
	if (p == NULL || name == NULL || unistr == NULL)
	{
		return;
	}

	v = NewUniStrValue(unistr);
	AddElement(p, NewElement(name, VALUE_UNISTR, 1, &v));
}