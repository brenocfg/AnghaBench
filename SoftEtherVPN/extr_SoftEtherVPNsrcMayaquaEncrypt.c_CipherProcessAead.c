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
struct TYPE_3__ {int IsAeadCipher; int Encrypt; int /*<<< orphan*/  Ctx; scalar_t__ IsNullCipher; } ;
typedef  TYPE_1__ CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_GET_TAG ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_SET_TAG ; 
 int EVP_CipherFinal_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int EVP_CipherInit_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 
 int EVP_CipherUpdate (int /*<<< orphan*/ ,void*,int*,void*,scalar_t__) ; 
 int /*<<< orphan*/  OpenSSL_Error () ; 

UINT CipherProcessAead(CIPHER *c, void *iv, void *tag, UINT tag_size, void *dest, void *src, UINT src_size, void *aad, UINT aad_size)
{
	int r = src_size;
	int r2 = 0;
	// Validate arguments
	if (c == NULL)
	{
		return 0;
	}
	else if (c->IsNullCipher)
	{
		Copy(dest, src, src_size);
		return src_size;
	}
	else if (c->IsAeadCipher == false || iv == NULL || tag == NULL || tag_size == 0 || dest == NULL || src == NULL || src_size == 0)
	{
		return 0;
	}

	if (EVP_CipherInit_ex(c->Ctx, NULL, NULL, NULL, iv, c->Encrypt) == false)
	{
		Debug("CipherProcessAead(): EVP_CipherInit_ex() failed with error: %s\n", OpenSSL_Error());
		return 0;
	}

	if (c->Encrypt == false)
	{
		if (EVP_CIPHER_CTX_ctrl(c->Ctx, EVP_CTRL_AEAD_SET_TAG, tag_size, tag) == false)
		{
			Debug("CipherProcessAead(): EVP_CIPHER_CTX_ctrl() failed to set the tag!\n");
			return 0;
		}
	}

	if (aad != NULL && aad_size != 0)
	{
		if (EVP_CipherUpdate(c->Ctx, NULL, &r, aad, aad_size) == false)
		{
			Debug("CipherProcessAead(): EVP_CipherUpdate() failed with error: %s\n", OpenSSL_Error());
			return 0;
		}
	}

	if (EVP_CipherUpdate(c->Ctx, dest, &r, src, src_size) == false)
	{
		Debug("CipherProcessAead(): EVP_CipherUpdate() failed with error: %s\n", OpenSSL_Error());
		return 0;
	}

	if (EVP_CipherFinal_ex(c->Ctx, ((UCHAR *)dest) + (UINT)r, &r2) == false)
	{
		Debug("CipherProcessAead(): EVP_CipherFinal_ex() failed with error: %s\n", OpenSSL_Error());
		return 0;
	}

	if (c->Encrypt)
	{
		if (EVP_CIPHER_CTX_ctrl(c->Ctx, EVP_CTRL_AEAD_GET_TAG, tag_size, tag) == false)
		{
			Debug("CipherProcessAead(): EVP_CIPHER_CTX_ctrl() failed to get the tag!\n");
			return 0;
		}
	}

	return r + r2;
}