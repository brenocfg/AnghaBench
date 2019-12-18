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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int KeySize; int /*<<< orphan*/  KeyValue; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  TYPE_1__ AES_KEY_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_padding (int /*<<< orphan*/ *,int) ; 
 int EVP_DecryptFinal_ex (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int EVP_DecryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int EVP_DecryptUpdate (int /*<<< orphan*/ *,void*,int*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_aes_128_cbc () ; 
 int /*<<< orphan*/  EVP_aes_192_cbc () ; 
 int /*<<< orphan*/  EVP_aes_256_cbc () ; 
 int /*<<< orphan*/  stderr ; 

void AesDecrypt(void *dest, void *src, UINT size, AES_KEY_VALUE *k, void *ivec)
{
	EVP_CIPHER_CTX *ctx = NULL;
	int dest_len = 0;
	int len = 0;
	int ret = 0;

	// Validate arguments
	if (dest == NULL || src == NULL || size == 0 || k == NULL || ivec == NULL)
	{
		return;
	}

	// Create and initialize the context
	ctx = EVP_CIPHER_CTX_new();

	if (!ctx)
	{
		ERR_print_errors_fp(stderr);
		return;
	}

	// Disable padding, as it's handled by IkeEncryptWithPadding()
	EVP_CIPHER_CTX_set_padding(ctx, false);

	// Initialize the decryption operation
	switch (k->KeySize)
	{
	case 16:
		ret = EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, k->KeyValue, ivec);
		break;

	case 24:
		ret = EVP_DecryptInit_ex(ctx, EVP_aes_192_cbc(), NULL, k->KeyValue, ivec);
		break;

	case 32:
		ret = EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, k->KeyValue, ivec);
		break;
	}

	if (ret != 1)
	{
		ERR_print_errors_fp(stderr);
		EVP_CIPHER_CTX_free(ctx);
		return;
	}

	// Provide the message to be decrypted and obtain the plaintext output
	ret = EVP_DecryptUpdate(ctx, dest, &dest_len, src, size);

	if (ret != 1)
	{
		ERR_print_errors_fp(stderr);
		EVP_CIPHER_CTX_free(ctx);
		return;
	}

	// Finalize the decryption
	ret = EVP_DecryptFinal_ex(ctx, (unsigned char *) dest + dest_len, &len);

	if (ret != 1)
	{
		ERR_print_errors_fp(stderr);
		EVP_CIPHER_CTX_free(ctx);
		return;
	}

	dest_len += len;

	// Clean up
	EVP_CIPHER_CTX_free(ctx);
}