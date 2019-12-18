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
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 scalar_t__ CompareBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int DumpBufW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReadDumpW (int /*<<< orphan*/ *) ; 

bool DumpBufWIfNecessary(BUF *b, wchar_t *filename)
{
	BUF *now;
	bool need = true;
	// Validate arguments
	if (b == NULL || filename == NULL)
	{
		return false;
	}

	now = ReadDumpW(filename);

	if (now != NULL)
	{
		if (CompareBuf(now, b))
		{
			need = false;
		}

		FreeBuf(now);
	}

	if (need == false)
	{
		return true;
	}
	else
	{
		return DumpBufW(b, filename);
	}
}