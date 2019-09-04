#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pem_password_cb ;
struct TYPE_8__ {char* password; } ;
struct TYPE_7__ {int private_key; int /*<<< orphan*/ * pkey; } ;
typedef  TYPE_1__ K ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_2__ CB_PARAM ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PEM_read_bio_PUBKEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * PEM_read_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ PKeyPasswordCallbackFunction ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 
 int /*<<< orphan*/ * d2i_PUBKEY_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_PrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openssl_lock ; 

K *BioToK(BIO *bio, bool private_key, bool text, char *password)
{
	EVP_PKEY *pkey;
	K *k;
	// Validate arguments
	if (bio == NULL)
	{
		return NULL;
	}

	if (password != NULL && StrLen(password) == 0)
	{
		password = NULL;
	}

	if (private_key == false)
	{
		// Public key
		if (text == false)
		{
			// Binary format
			pkey = d2i_PUBKEY_bio(bio, NULL);
			if (pkey == NULL)
			{
				return NULL;
			}
		}
		else
		{
			// Text format
			CB_PARAM cb;
			cb.password = password;
			Lock(openssl_lock);
			{
				pkey = PEM_read_bio_PUBKEY(bio, NULL, (pem_password_cb *)PKeyPasswordCallbackFunction, &cb);
			}
			Unlock(openssl_lock);
			if (pkey == NULL)
			{
				return NULL;
			}
		}
	}
	else
	{
		if (text == false)
		{
			// Binary format
			Lock(openssl_lock);
			{
				pkey = d2i_PrivateKey_bio(bio, NULL);
			}
			Unlock(openssl_lock);
			if (pkey == NULL)
			{
				return NULL;
			}
		}
		else
		{
			// Text format
			CB_PARAM cb;
			cb.password = password;
			Lock(openssl_lock);
			{
				pkey = PEM_read_bio_PrivateKey(bio, NULL, (pem_password_cb *)PKeyPasswordCallbackFunction, &cb);
			}
			Unlock(openssl_lock);
			if (pkey == NULL)
			{
				return NULL;
			}
		}
	}

	k = ZeroMalloc(sizeof(K));
	k->pkey = pkey;
	k->private_key = private_key;

	return k;
}