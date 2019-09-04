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
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XToBuf (int /*<<< orphan*/ *,int) ; 

void PackAddX(PACK *p, char *name, X *x)
{
	BUF *b;
	// Validate arguments
	if (p == NULL || name == NULL || x == NULL)
	{
		return;
	}

	b = XToBuf(x, false);
	if (b == NULL)
	{
		return;
	}

	PackAddBuf(p, name, b);
	FreeBuf(b);
}