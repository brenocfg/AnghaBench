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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {scalar_t__ Size; scalar_t__ Current; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */

UINT ReadBufRemainSize(BUF *b)
{
	// Validate arguments
	if (b == NULL)
	{
		return 0;
	}

	if (b->Size < b->Current)
	{
		return 0;
	}

	return b->Size - b->Current;
}