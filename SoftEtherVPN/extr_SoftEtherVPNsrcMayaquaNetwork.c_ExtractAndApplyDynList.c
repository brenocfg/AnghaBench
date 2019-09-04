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
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddDynList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PackGetBuf (int /*<<< orphan*/ *,char*) ; 

void ExtractAndApplyDynList(PACK *p)
{
	BUF *b;
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	b = PackGetBuf(p, "DynList");
	if (b == NULL)
	{
		return;
	}

	AddDynList(b);

	FreeBuf(b);
}