#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 scalar_t__ CalcCompress (int /*<<< orphan*/ ) ; 
 scalar_t__ Compress (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Malloc (scalar_t__) ; 
 TYPE_1__* NewBuf () ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WriteBufInt (TYPE_1__*,int /*<<< orphan*/ ) ; 

BUF *CompressBuf(BUF *src_buf)
{
	UINT dst_size;
	UCHAR *dst_buf;
	BUF *b;
	// Validate arguments
	if (src_buf == NULL)
	{
		return NULL;
	}

	dst_size = CalcCompress(src_buf->Size);
	dst_buf = Malloc(dst_size);

	dst_size = Compress(dst_buf, dst_size, src_buf->Buf, src_buf->Size);

	if (dst_size == 0)
	{
		Free(dst_buf);
		return NULL;
	}

	b = NewBuf();
	WriteBufInt(b, src_buf->Size);
	WriteBuf(b, dst_buf, dst_size);

	Free(dst_buf);

	return b;
}