#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_5__ {int /*<<< orphan*/  rowcontext; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__* CopyOutState ;

/* Variables and functions */
 int /*<<< orphan*/  BinarySignature ; 
 int /*<<< orphan*/  CopySendData (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CopySendInt32 (TYPE_1__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 

void
AppendCopyBinaryHeaders(CopyOutState headerOutputState)
{
	const int32 zero = 0;
	MemoryContext oldContext = MemoryContextSwitchTo(headerOutputState->rowcontext);

	/* Signature */
	CopySendData(headerOutputState, BinarySignature, 11);

	/* Flags field (no OIDs) */
	CopySendInt32(headerOutputState, zero);

	/* No header extension */
	CopySendInt32(headerOutputState, zero);

	MemoryContextSwitchTo(oldContext);
}