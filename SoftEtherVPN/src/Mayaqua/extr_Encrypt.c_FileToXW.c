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
 int /*<<< orphan*/ * BufToX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int IsBase64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ReadDumpW (int /*<<< orphan*/ *) ; 

X *FileToXW(wchar_t *filename)
{
	bool text;
	BUF *b;
	X *x;
	// Validate arguments
	if (filename == NULL)
	{
		return NULL;
	}

	b = ReadDumpW(filename);
	text = IsBase64(b);

	x = BufToX(b, text);
	FreeBuf(b);

	return x;
}