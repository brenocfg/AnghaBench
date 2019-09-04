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
struct TYPE_4__ {void* Data; void* Name; } ;
typedef  TYPE_1__ HTTP_VALUE ;

/* Variables and functions */
 void* CopyStr (char*) ; 
 int /*<<< orphan*/  Trim (void*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

HTTP_VALUE *NewHttpValue(char *name, char *data)
{
	HTTP_VALUE *v;
	// Validate arguments
	if (name == NULL || data == NULL)
	{
		return NULL;
	}

	v = ZeroMalloc(sizeof(HTTP_VALUE));

	v->Name = CopyStr(name);
	v->Data = CopyStr(data);

	Trim(v->Name);
	Trim(v->Data);

	return v;
}