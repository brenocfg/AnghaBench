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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  KeySchedule; } ;
typedef  int /*<<< orphan*/  DES_cblock ;
typedef  TYPE_1__ DES_KEY_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,void*,int) ; 
 int DES_IV_SIZE ; 
 int /*<<< orphan*/  DES_cbc_encrypt (void*,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void DesDecrypt(void *dest, void *src, UINT size, DES_KEY_VALUE *k, void *ivec)
{
	UCHAR ivec_copy[DES_IV_SIZE];
	// Validate arguments
	if (dest == NULL || src == NULL || size == 0 || k == NULL || ivec == NULL)
	{
		return;
	}

	Copy(ivec_copy, ivec, DES_IV_SIZE);

	DES_cbc_encrypt(src, dest, size,
		k->KeySchedule,
		(DES_cblock *)ivec_copy,
		0);
}