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
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

BUF *MemToBuf(void *data, UINT size)
{
	BUF *b;
	// Validate arguments
	if (data == NULL && size != 0)
	{
		return NULL;
	}

	b = NewBuf();
	WriteBuf(b, data, size);
	SeekBuf(b, 0, 0);

	return b;
}