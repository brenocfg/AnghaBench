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
typedef  int /*<<< orphan*/  hash ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  pkey; } ;
typedef  TYPE_1__ K ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_RSA ; 
 scalar_t__ EVP_PKEY_base_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_get0_RSA (int /*<<< orphan*/ ) ; 
 int HashForSign (int /*<<< orphan*/ *,int,void*,int) ; 
 int RSA_KEY_SIZE ; 
 int /*<<< orphan*/  RSA_PKCS1_PADDING ; 
 scalar_t__ RSA_private_encrypt (int,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SIGN_HASH_SIZE ; 
 int /*<<< orphan*/  Zero (void*,int) ; 

bool RsaSignEx(void *dst, void *src, UINT size, K *k, UINT bits)
{
	UCHAR hash[SIGN_HASH_SIZE];
	// Validate arguments
	if (dst == NULL || src == NULL || k == NULL || EVP_PKEY_base_id(k->pkey) != EVP_PKEY_RSA)
	{
		return false;
	}
	if (bits == 0)
	{
		bits = RSA_KEY_SIZE;
	}

	Zero(dst, bits / 8);

	// Hash
	if (HashForSign(hash, sizeof(hash), src, size) == false)
	{
		return false;
	}

	// Signature
	if (RSA_private_encrypt(sizeof(hash), hash, dst, EVP_PKEY_get0_RSA(k->pkey), RSA_PKCS1_PADDING) <= 0)
	{
		return false;
	}

	return true;
}