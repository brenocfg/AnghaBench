#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int Size; int /*<<< orphan*/  dh; } ;
typedef  TYPE_1__ DH_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BinToBigNum (void*,int) ; 
 int /*<<< orphan*/ * Clone (void*,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int DH_compute_key (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (void*,int) ; 

bool DhCompute(DH_CTX *dh, void *dst_priv_key, void *src_pub_key, UINT key_size)
{
	int i;
	BIGNUM *bn;
	bool ret = false;
	// Validate arguments
	if (dh == NULL || dst_priv_key == NULL || src_pub_key == NULL)
	{
		return false;
	}
	if (key_size > dh->Size)
	{
		return false;
	}

	bn = BinToBigNum(src_pub_key, key_size);

	i = DH_compute_key(dst_priv_key, bn, dh->dh);

	if (i == dh->Size)
	{
		ret = true;
	}
	else if ((UINT)i < dh->Size)
	{
		UCHAR *dst2 = Clone(dst_priv_key, i);

		Zero(dst_priv_key, dh->Size);

		Copy(((UCHAR *)dst_priv_key) + (dh->Size - i), dst2, i);

		ret = true;
	}

	BN_free(bn);

	return ret;
}