#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  depth; int /*<<< orphan*/  b; } ;
typedef  int /*<<< orphan*/  ITEM ;
typedef  TYPE_1__ CFG_ENUM_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool CfgEnumItemProc(ITEM *t, void *param)
{
	CFG_ENUM_PARAM *p;
	// Validate arguments
	if (t == NULL || param == NULL)
	{
		return false;
	}

	p = (CFG_ENUM_PARAM *)param;
	CfgAddItemText(p->b, t, p->depth);

	return true;
}