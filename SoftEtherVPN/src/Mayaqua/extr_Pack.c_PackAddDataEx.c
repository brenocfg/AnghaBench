#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VALUE ;
typedef  size_t UINT ;
struct TYPE_5__ {size_t num_value; int JsonHint_IsArray; int /*<<< orphan*/ ** values; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ ELEMENT ;

/* Variables and functions */
 int AddElement (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FreeValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* GetElement (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewDataValue (void*,size_t) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  VALUE_DATA ; 
 void* ZeroMallocEx (int,int) ; 

ELEMENT *PackAddDataEx(PACK *p, char *name, void *data, UINT size, UINT index, UINT total)
{
	VALUE *v;
	ELEMENT *e;
	// Validate arguments
	if (p == NULL || data == NULL || name == NULL || total == 0)
	{
		return NULL;
	}

	v = NewDataValue(data, size);
	e = GetElement(p, name, VALUE_DATA);
	if (e != NULL)
	{
		if (e->num_value >= total)
		{
			FreeValue(e->values[index], VALUE_DATA);
			e->values[index] = v;
		}
		else
		{
			FreeValue(v, VALUE_DATA);
		}
	}
	else
	{
		e = ZeroMallocEx(sizeof(ELEMENT), true);
		StrCpy(e->name, sizeof(e->name), name);
		e->num_value = total;
		e->type = VALUE_DATA;
		e->values = ZeroMallocEx(sizeof(VALUE *) * total, true);
		e->values[index] = v;
		if (AddElement(p, e) == false)
		{
			return NULL;
		}
	}

	e->JsonHint_IsArray = true;

	return e;
}