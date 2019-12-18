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
struct TYPE_3__ {int /*<<< orphan*/  elements; } ;
typedef  TYPE_1__ PACK ;
typedef  int /*<<< orphan*/  ELEMENT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBufInt (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WriteElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void WritePack(BUF *b, PACK *p)
{
	UINT i;
	// Validate arguments
	if (b == NULL || p == NULL)
	{
		return;
	}

	// The number of ELEMENTs
	WriteBufInt(b, LIST_NUM(p->elements));

	// Write the ELEMENT
	for (i = 0;i < LIST_NUM(p->elements);i++)
	{
		ELEMENT *e = LIST_DATA(p->elements, i);
		WriteElement(b, e);
	}
}