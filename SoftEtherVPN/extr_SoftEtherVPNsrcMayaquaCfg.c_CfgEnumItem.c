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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Items; } ;
typedef  int /*<<< orphan*/  ITEM ;
typedef  TYPE_1__ FOLDER ;
typedef  int (* ENUM_ITEM ) (int /*<<< orphan*/ *,void*) ;

/* Variables and functions */
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

void CfgEnumItem(FOLDER *f, ENUM_ITEM proc, void *param)
{
	UINT i;
	// Validate arguments
	if (f == NULL || proc == NULL)
	{
		return;
	}
	
	for (i = 0;i < LIST_NUM(f->Items);i++)
	{
		ITEM *tt = LIST_DATA(f->Items, i);
		if (proc(tt, param) == false)
		{
			break;
		}
	}
}