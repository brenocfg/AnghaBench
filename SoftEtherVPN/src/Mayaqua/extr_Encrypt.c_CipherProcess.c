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
struct TYPE_3__ {int /*<<< orphan*/  Ctx; int /*<<< orphan*/  Encrypt; scalar_t__ IsNullCipher; } ;
typedef  TYPE_1__ CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,void*,int) ; 
 scalar_t__ EVP_CipherFinal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ EVP_CipherInit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_CipherUpdate (int /*<<< orphan*/ ,void*,int*,void*,int) ; 

UINT CipherProcess(CIPHER *c, void *iv, void *dest, void *src, UINT size)
{
	int r = size;
	int r2 = 0;
	if (c != NULL && c->IsNullCipher)
	{
		if (dest != src)
		{
			Copy(dest, src, size);
		}
		return size;
	}
	// Validate arguments
	if (c == NULL || iv == NULL || dest == NULL || src == NULL || size == 0)
	{
		return 0;
	}

	if (EVP_CipherInit(c->Ctx, NULL, NULL, iv, c->Encrypt) == 0)
	{
		return 0;
	}

	if (EVP_CipherUpdate(c->Ctx, dest, &r, src, size) == 0)
	{
		return 0;
	}

	if (EVP_CipherFinal(c->Ctx, ((UCHAR *)dest) + (UINT)r, &r2) == 0)
	{
		return 0;
	}

	return r + r2;
}