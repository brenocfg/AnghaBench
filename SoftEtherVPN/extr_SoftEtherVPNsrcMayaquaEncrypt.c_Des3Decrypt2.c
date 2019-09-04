#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {int /*<<< orphan*/  KeySchedule; } ;
typedef  int /*<<< orphan*/  DES_cblock ;
typedef  TYPE_1__ DES_KEY_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,void*,int) ; 
 int DES_IV_SIZE ; 
 int /*<<< orphan*/  DES_ede3_cbc_encrypt (void*,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void Des3Decrypt2(void *dest, void *src, UINT size, DES_KEY_VALUE *k1, DES_KEY_VALUE *k2, DES_KEY_VALUE *k3, void *ivec)
{
	UCHAR ivec_copy[DES_IV_SIZE];
	// Validate arguments
	if (dest == NULL || src == NULL || size == 0 || k1 == NULL || k2 == NULL || k3 == NULL || ivec == NULL)
	{
		return;
	}

	Copy(ivec_copy, ivec, DES_IV_SIZE);

	DES_ede3_cbc_encrypt(src, dest, size,
		k1->KeySchedule,
		k2->KeySchedule,
		k3->KeySchedule,
		(DES_cblock *)ivec_copy,
		0);
}