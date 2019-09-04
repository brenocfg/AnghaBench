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
struct TYPE_4__ {struct TYPE_4__* Data; } ;
typedef  TYPE_1__ SSTP_ATTRIBUTE ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 

void SstpFreeAttribute(SSTP_ATTRIBUTE *a)
{
	// Validate arguments
	if (a == NULL)
	{
		return;
	}

	Free(a->Data);

	Free(a);
}