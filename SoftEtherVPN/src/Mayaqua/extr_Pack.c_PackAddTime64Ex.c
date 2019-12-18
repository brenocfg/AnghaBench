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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int JsonHint_IsDateTime; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ ELEMENT ;

/* Variables and functions */
 TYPE_1__* PackAddInt64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ELEMENT *PackAddTime64Ex(PACK *p, char *name, UINT64 i, UINT index, UINT total)
{
	ELEMENT *e = PackAddInt64Ex(p, name, i, index, total);
	if (e != NULL)
	{
		e->JsonHint_IsDateTime = true;
	}
	return e;
}