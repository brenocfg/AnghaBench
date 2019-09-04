#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  VALUE ;
typedef  size_t UINT ;
struct TYPE_4__ {size_t num_value; int /*<<< orphan*/ ** values; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  AddElement (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FreeValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* GetElement (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewUniStrValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  VALUE_UNISTR ; 
 void* ZeroMallocEx (int,int) ; 

void PackAddUniStrEx(PACK *p, char *name, wchar_t *unistr, UINT index, UINT total)
{
	VALUE *v;
	ELEMENT *e;
	// Validate arguments
	if (p == NULL || name == NULL || unistr == NULL || total == 0)
	{
		return;
	}

	v = NewUniStrValue(unistr);
	e = GetElement(p, name, VALUE_UNISTR);
	if (e != NULL)
	{
		if (e->num_value <= total)
		{
			e->values[index] = v;
		}
		else
		{
			FreeValue(v, VALUE_UNISTR);
		}
	}
	else
	{
		e = ZeroMallocEx(sizeof(ELEMENT), true);
		StrCpy(e->name, sizeof(e->name), name);
		e->num_value = total;
		e->type = VALUE_UNISTR;
		e->values = ZeroMallocEx(sizeof(VALUE *) * total, true);
		e->values[index] = v;
		AddElement(p, e);
	}
}