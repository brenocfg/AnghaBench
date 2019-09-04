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
typedef  int /*<<< orphan*/  hash_data ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int private_key; int /*<<< orphan*/  pkey; } ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_1__ K ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_RSA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int HashForSign (int /*<<< orphan*/ *,int,void*,int) ; 
 int MAX (int,int) ; 
 int RSA_KEY_SIZE ; 
 int /*<<< orphan*/  RSA_PKCS1_PADDING ; 
 scalar_t__ RSA_public_decrypt (int,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RSA_size (int /*<<< orphan*/ *) ; 
 int SIGN_HASH_SIZE ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

bool RsaVerifyEx(void *data, UINT data_size, void *sign, K *k, UINT bits)
{
	UCHAR hash_data[SIGN_HASH_SIZE];
	UCHAR *decrypt_data;
	RSA *rsa;
	UINT rsa_size;
	// Validate arguments
	if (data == NULL || sign == NULL || k == NULL || k->private_key != false)
	{
		return false;
	}
	if (bits == 0)
	{
		bits = RSA_KEY_SIZE;
	}

	rsa = EVP_PKEY_get0_RSA(k->pkey);
	if (rsa == NULL)
	{
		return false;
	}

	// Hash the data
	if (HashForSign(hash_data, sizeof(hash_data), data, data_size) == false)
	{
		return false;
	}

	rsa_size = RSA_size(rsa);
	rsa_size = MAX(rsa_size, 1024); // For just in case
	decrypt_data = ZeroMalloc(rsa_size);

	// Decode the signature
	if (RSA_public_decrypt(bits / 8, sign, decrypt_data, rsa, RSA_PKCS1_PADDING) <= 0)
	{
		Free(decrypt_data);
		return false;
	}

	// Comparison
	if (Cmp(decrypt_data, hash_data, SIGN_HASH_SIZE) != 0)
	{
		Free(decrypt_data);
		return false;
	}

	Free(decrypt_data);

	return true;
}