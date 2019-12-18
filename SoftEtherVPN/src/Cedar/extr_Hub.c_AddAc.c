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
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  AC ;

/* Variables and functions */
 int /*<<< orphan*/  Clone (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_HUB_ACS ; 
 int /*<<< orphan*/  NormalizeAcList (int /*<<< orphan*/ *) ; 

void AddAc(LIST *o, AC *ac)
{
	// Validate arguments
	if (o == NULL || ac == NULL)
	{
		return;
	}

	if (LIST_NUM(o) < MAX_HUB_ACS)
	{
		Insert(o, Clone(ac, sizeof(AC)));

		NormalizeAcList(o);
	}
}