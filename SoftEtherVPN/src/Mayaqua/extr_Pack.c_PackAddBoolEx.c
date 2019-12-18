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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int JsonHint_IsBool; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ ELEMENT ;

/* Variables and functions */
 TYPE_1__* PackAddIntEx (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ELEMENT *PackAddBoolEx(PACK *p, char *name, bool b, UINT index, UINT total)
{
	ELEMENT *e = PackAddIntEx(p, name, b ? 1 : 0, index, total);
	if (e != NULL)
	{
		e->JsonHint_IsBool = true;
	}
	return e;
}