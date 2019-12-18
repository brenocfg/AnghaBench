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
typedef  int /*<<< orphan*/  VALUE ;
typedef  int UINT ;
struct TYPE_4__ {int num_value; int type; int /*<<< orphan*/ ** values; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

ELEMENT *NewElement(char *name, UINT type, UINT num_value, VALUE **values)
{
	ELEMENT *e;
	UINT i;
	// Validate arguments
	if (name == NULL || num_value == 0 || values == NULL)
	{
		return NULL;
	}

	// Memory allocation
	e = ZeroMalloc(sizeof(ELEMENT));
	StrCpy(e->name, sizeof(e->name), name);
	e->num_value = num_value;
	e->type = type;

	// Copy of the pointer list to the element
	e->values = (VALUE **)ZeroMalloc(sizeof(VALUE *) * num_value);
	for (i = 0;i < e->num_value;i++)
	{
		e->values[i] = values[i];
	}

	return e;
}