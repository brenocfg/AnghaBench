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
struct TYPE_4__ {int /*<<< orphan*/  ValueList; void* Version; void* Target; void* Method; } ;
typedef  TYPE_1__ HTTP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/ * CompareHttpValue ; 
 void* CopyStr (char*) ; 
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

HTTP_HEADER *NewHttpHeaderEx(char *method, char *target, char *version, bool no_sort)
{
	HTTP_HEADER *header;
	// Validate arguments
	if (method == NULL || target == NULL || version == NULL)
	{
		return NULL;
	}

	header = ZeroMalloc(sizeof(HTTP_HEADER));

	header->Method = CopyStr(method);
	header->Target = CopyStr(target);
	header->Version = CopyStr(version);
	header->ValueList = NewListFast(no_sort ? NULL : CompareHttpValue);

	return header;
}