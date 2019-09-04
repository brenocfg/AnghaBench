#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ValueList; } ;
struct TYPE_7__ {char* Name; } ;
typedef  TYPE_1__ HTTP_VALUE ;
typedef  TYPE_2__ HTTP_HEADER ;

/* Variables and functions */
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 

HTTP_VALUE *GetHttpValue(HTTP_HEADER *header, char *name)
{
	HTTP_VALUE *v, t;
	// Validate arguments
	if (header == NULL || name == NULL)
	{
		return NULL;
	}

	t.Name = name;
	v = Search(header->ValueList, &t);
	if (v == NULL)
	{
		return NULL;
	}

	return v;
}