#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct evp_cipher_ctx_st {int dummy; } ;
struct TYPE_4__ {int IsNullCipher; int IsAeadCipher; int /*<<< orphan*/ * Cipher; int /*<<< orphan*/  IvSize; int /*<<< orphan*/  KeySize; int /*<<< orphan*/  BlockSize; void* Ctx; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_init (void*) ; 
 void* EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CIPHER_block_size (int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_iv_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_key_length (int /*<<< orphan*/ *) ; 
 int EVP_CIPH_FLAG_AEAD_CIPHER ; 
 int /*<<< orphan*/ * EVP_get_cipherbyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeCipher (TYPE_1__*) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 void* ZeroMalloc (int) ; 

CIPHER *NewCipher(char *name)
{
	CIPHER *c;
	// Validate arguments
	if (name == NULL)
	{
		return NULL;
	}

	c = ZeroMalloc(sizeof(CIPHER));

	StrCpy(c->Name, sizeof(c->Name), name);

	if (StrCmpi(name, "[null-cipher]") == 0 ||
		StrCmpi(name, "NULL") == 0 ||
		IsEmptyStr(name))
	{
		c->IsNullCipher = true;
		return c;
	}

	c->Cipher = EVP_get_cipherbyname(c->Name);
	if (c->Cipher == NULL)
	{
		Debug("NewCipher(): Cipher %s not found by EVP_get_cipherbyname().\n", c->Name);
		FreeCipher(c);
		return NULL;
	}

#if OPENSSL_VERSION_NUMBER >= 0x10100000L
	c->Ctx = EVP_CIPHER_CTX_new();
#else
	c->Ctx = ZeroMalloc(sizeof(struct evp_cipher_ctx_st));
	EVP_CIPHER_CTX_init(c->Ctx);
#endif

	c->IsAeadCipher = EVP_CIPHER_flags(c->Cipher) & EVP_CIPH_FLAG_AEAD_CIPHER;
	c->BlockSize = EVP_CIPHER_block_size(c->Cipher);
	c->KeySize = EVP_CIPHER_key_length(c->Cipher);
	c->IvSize = EVP_CIPHER_iv_length(c->Cipher);

	return c;
}