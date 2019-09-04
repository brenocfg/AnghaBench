#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* Name; void* Value; } ;
typedef  TYPE_1__ STRMAP_ENTRY ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 scalar_t__ Search (int /*<<< orphan*/ *,TYPE_1__*) ; 

void *StrMapSearch(LIST *map, char *key)
{
	STRMAP_ENTRY tmp, *result;
	tmp.Name = key;
	result = (STRMAP_ENTRY*)Search(map, &tmp);
	if(result != NULL)
	{
		return result->Value;
	}
	return NULL;
}