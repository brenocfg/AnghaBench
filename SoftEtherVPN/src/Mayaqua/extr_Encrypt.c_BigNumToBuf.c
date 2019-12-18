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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2bin (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZeroMalloc (int /*<<< orphan*/ ) ; 

BUF *BigNumToBuf(const BIGNUM *bn)
{
	UINT size;
	UCHAR *tmp;
	BUF *b;
	// Validate arguments
	if (bn == NULL)
	{
		return NULL;
	}

	size = BN_num_bytes(bn);
	tmp = ZeroMalloc(size);
	BN_bn2bin(bn, tmp);

	b = NewBuf();
	WriteBuf(b, tmp, size);
	Free(tmp);

	SeekBuf(b, 0, 0);

	return b;
}