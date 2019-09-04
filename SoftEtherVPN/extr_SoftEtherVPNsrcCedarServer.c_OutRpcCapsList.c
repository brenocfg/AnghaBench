#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
struct TYPE_5__ {int /*<<< orphan*/  CapsList; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ CAPSLIST ;
typedef  TYPE_2__ CAPS ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcCapsList(PACK *p, CAPSLIST *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	for (i = 0;i < LIST_NUM(t->CapsList);i++)
	{
		char tmp[MAX_SIZE];
		CAPS *c = LIST_DATA(t->CapsList, i);

		Format(tmp, sizeof(tmp), "caps_%s", c->Name);
		PackAddInt(p, tmp, c->Value);
	}
}