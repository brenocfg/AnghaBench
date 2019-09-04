#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pem_password_cb ;
struct TYPE_6__ {char* password; } ;
struct TYPE_5__ {int /*<<< orphan*/  pkey; scalar_t__ private_key; } ;
typedef  TYPE_1__ K ;
typedef  TYPE_2__ CB_PARAM ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_des_ede3_cbc () ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewBio () ; 
 int /*<<< orphan*/  PEM_write_bio_PUBKEY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PEM_write_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ PKeyPasswordCallbackFunction ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2d_PUBKEY_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2d_PrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openssl_lock ; 

BIO *KToBio(K *k, bool text, char *password)
{
	BIO *bio;
	// Validate arguments
	if (k == NULL)
	{
		return NULL;
	}

	bio = NewBio();

	if (k->private_key)
	{
		// Secret key
		if (text == false)
		{
			// Binary format
			Lock(openssl_lock);
			{
				i2d_PrivateKey_bio(bio, k->pkey);
			}
			Unlock(openssl_lock);
		}
		else
		{
			// Text format
			if (password == 0 || StrLen(password) == 0)
			{
				// No encryption
				Lock(openssl_lock);
				{
					PEM_write_bio_PrivateKey(bio, k->pkey, NULL, NULL, 0, NULL, NULL);
				}
				Unlock(openssl_lock);
			}
			else
			{
				// Encrypt
				CB_PARAM cb;
				cb.password = password;
				Lock(openssl_lock);
				{
					PEM_write_bio_PrivateKey(bio, k->pkey, EVP_des_ede3_cbc(),
						NULL, 0, (pem_password_cb *)PKeyPasswordCallbackFunction, &cb);
				}
				Unlock(openssl_lock);
			}
		}
	}
	else
	{
		// Public key
		if (text == false)
		{
			// Binary format
			Lock(openssl_lock);
			{
				i2d_PUBKEY_bio(bio, k->pkey);
			}
			Unlock(openssl_lock);
		}
		else
		{
			// Text format
			Lock(openssl_lock);
			{
				PEM_write_bio_PUBKEY(bio, k->pkey);
			}
			Unlock(openssl_lock);
		}
	}

	return bio;
}