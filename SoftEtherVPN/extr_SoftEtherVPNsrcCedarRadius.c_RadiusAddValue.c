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
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 int /*<<< orphan*/  WriteBufChar (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteBufInt (int /*<<< orphan*/ *,scalar_t__) ; 

void RadiusAddValue(BUF *b, UCHAR t, UINT v, UCHAR vt, void *data, UINT size)
{
	UINT len;
	// Validate arguments
	if (b == NULL || (data == NULL && size != 0))
	{
		return;
	}

	// type
	WriteBufChar(b, t);

	// length
	len = 2 + size;
	if (t == 26)
	{
		len += 6;
	}
	WriteBufChar(b, (UCHAR)len);

	if (t != 26)
	{
		// value
		WriteBuf(b, data, size);
	}
	else
	{
		// vendor
		WriteBufInt(b, v);

		// vendor type
		WriteBufChar(b, vt);

		// length2
		len = size + 2;
		WriteBufChar(b, (UCHAR)len);

		// value
		WriteBuf(b, data, size);
	}
}