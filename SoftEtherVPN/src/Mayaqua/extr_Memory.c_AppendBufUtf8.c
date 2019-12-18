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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 scalar_t__ CalcUniToUtf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToUtf8 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ZeroMalloc (scalar_t__) ; 

void AppendBufUtf8(BUF *b, wchar_t *str)
{
	UINT size;
	UCHAR *data;
	// Validate arguments
	if (b == NULL || str == NULL)
	{
		return;
	}

	size = CalcUniToUtf8(str) + 1;
	data = ZeroMalloc(size);

	UniToUtf8(data, size, str);

	WriteBuf(b, data, size - 1);

	Free(data);
}