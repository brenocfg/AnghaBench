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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  ReadBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BUF *ReadBufFromBuf(BUF *b, UINT size)
{
	BUF *ret;
	UCHAR *data;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	data = Malloc(size);
	if (ReadBuf(b, data, size) != size)
	{
		Free(data);
		return NULL;
	}

	ret = NewBuf();
	WriteBuf(ret, data, size);
	SeekBuf(ret, 0, 0);

	Free(data);

	return ret;
}