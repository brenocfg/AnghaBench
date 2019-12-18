#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ Size; scalar_t__ Current; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 TYPE_1__* ReadBufFromBuf (TYPE_1__*,scalar_t__) ; 

BUF *ReadRemainBuf(BUF *b)
{
	UINT size;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	if (b->Size < b->Current)
	{
		return NULL;
	}

	size = b->Size - b->Current;

	return ReadBufFromBuf(b, size);
}