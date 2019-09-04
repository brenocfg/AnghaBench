#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {scalar_t__ Size; scalar_t__ Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Malloc (int /*<<< orphan*/ ) ; 
 TYPE_1__* NewBuf () ; 
 int /*<<< orphan*/  ReadBufInt (TYPE_1__*) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Uncompress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BUF *UncompressBuf(BUF *src_buf)
{
	UINT dst_size, dst_size2;
	UCHAR *dst;
	BUF *b;
	// Validate arguments
	if (src_buf == NULL)
	{
		return NULL;
	}

	SeekBuf(src_buf, 0, 0);
	dst_size = ReadBufInt(src_buf);

	dst = Malloc(dst_size);

	dst_size2 = Uncompress(dst, dst_size, ((UCHAR *)src_buf->Buf) + sizeof(UINT), src_buf->Size - sizeof(UINT));

	b = NewBuf();
	WriteBuf(b, dst, dst_size2);
	Free(dst);

	return b;
}