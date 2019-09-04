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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int DumpBufW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XToBuf (int /*<<< orphan*/ *,int) ; 

bool XToFileW(X *x, wchar_t *filename, bool text)
{
	BUF *b;
	bool ret;
	// Validate arguments
	if (x == NULL || filename == NULL)
	{
		return false;
	}

	b = XToBuf(x, text);
	if (b == NULL)
	{
		return false;
	}

	ret = DumpBufW(b, filename);
	FreeBuf(b);

	return ret;
}