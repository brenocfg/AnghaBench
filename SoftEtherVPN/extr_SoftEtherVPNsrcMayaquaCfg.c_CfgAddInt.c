#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  ITEM ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgCreateItem (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ITEM_TYPE_INT ; 

ITEM *CfgAddInt(FOLDER *f, char *name, UINT i)
{
	// Validate arguments
	if (f == NULL || name == NULL)
	{
		return NULL;
	}
	return CfgCreateItem(f, name, ITEM_TYPE_INT, &i, sizeof(UINT));
}