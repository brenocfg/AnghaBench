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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  AddInt64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IsInt64InList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void AddInt64Distinct(LIST *o, UINT64 i)
{
	// Validate arguments
	if (o == NULL)
	{
		return;
	}

	if (IsInt64InList(o, i) == false)
	{
		AddInt64(o, i);
	}
}