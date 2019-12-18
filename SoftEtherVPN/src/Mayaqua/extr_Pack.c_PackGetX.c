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
 int /*<<< orphan*/ * BufToX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PackGetBuf (int /*<<< orphan*/ *,char*) ; 

X *PackGetX(PACK *p, char *name)
{
	X *x;
	BUF *b;
	// Validate arguments
	if (p == NULL || name == NULL)
	{
		return NULL;
	}

	b = PackGetBuf(p, name);
	if (b == NULL)
	{
		return NULL;
	}

	x = BufToX(b, false);

	if (x == NULL)
	{
		x = BufToX(b, true);
	}

	FreeBuf(b);

	return x;
}