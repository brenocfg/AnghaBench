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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  AC ;

/* Variables and functions */
 int /*<<< orphan*/  AddAc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DelAllAc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 

void SetAcList(LIST *o, LIST *src)
{
	UINT i;
	// Validate arguments
	if (o == NULL || src == NULL)
	{
		return;
	}

	DelAllAc(o);

	for (i = 0;i < LIST_NUM(src);i++)
	{
		AC *ac = LIST_DATA(src, i);

		AddAc(o, ac);
	}
}