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
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ ) ; 
 TYPE_1__* Search (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * TableList ; 

TABLE *FindTable(char *name)
{
	TABLE *t, tt;
	// Validate arguments
	if (name == NULL || TableList == NULL)
	{
		return NULL;
	}

	tt.name = CopyStr(name);
	t = Search(TableList, &tt);
	Free(tt.name);

	return t;
}