#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp1600 ;
typedef  int UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_8__ {TYPE_2__* Key; } ;
struct TYPE_7__ {TYPE_1__* Crypto; } ;
struct TYPE_6__ {int BlockSize; } ;
typedef  TYPE_3__ IKE_CRYPTO_PARAM ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (scalar_t__*,void*,int) ; 
 int /*<<< orphan*/  Free (scalar_t__*) ; 
 int /*<<< orphan*/ * IkeEncrypt (scalar_t__*,int,TYPE_3__*) ; 
 scalar_t__* Malloc (int) ; 

BUF *IkeEncryptWithPadding(void *data, UINT size, IKE_CRYPTO_PARAM *cparam)
{
	UINT total_size;
	UINT i;
	UCHAR n = 0;
	UCHAR *tmp;
	BUF *ret;
	UCHAR tmp1600[1600];
	bool no_free = false;
	// Validate arguments
	if (data == NULL || cparam == NULL)
	{
		return NULL;
	}

	total_size = ((size / cparam->Key->Crypto->BlockSize) + ((size % cparam->Key->Crypto->BlockSize) == 0 ? 0 : 1))
		* cparam->Key->Crypto->BlockSize;
	if (total_size == 0)
	{
		total_size = cparam->Key->Crypto->BlockSize;
	}

	if (total_size > sizeof(tmp1600))
	{
		tmp = Malloc(total_size);
	}
	else
	{
		tmp = tmp1600;
		no_free = true;
	}

	Copy(tmp, data, size);

	for (i = size;i < total_size;i++)
	{
		tmp[i] = ++n;
	}

	ret = IkeEncrypt(tmp, total_size, cparam);

	if (no_free == false)
	{
		Free(tmp);
	}

	return ret;
}