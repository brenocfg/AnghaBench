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
struct TYPE_3__ {scalar_t__ Current; scalar_t__ Size; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */

void ClearBuf(BUF *b)
{
	// Validate arguments
	if (b == NULL)
	{
		return;
	}

	b->Size = 0;
	b->Current = 0;
}