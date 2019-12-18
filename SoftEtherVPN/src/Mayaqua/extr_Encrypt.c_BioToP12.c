#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PKCS12 ;
typedef  int /*<<< orphan*/  P12 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PKCS12ToP12 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_PKCS12_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openssl_lock ; 

P12 *BioToP12(BIO *bio)
{
	PKCS12 *pkcs12;
	// Validate arguments
	if (bio == NULL)
	{
		return NULL;
	}

	// Conversion
	Lock(openssl_lock);
	{
		pkcs12 = d2i_PKCS12_bio(bio, NULL);
	}
	Unlock(openssl_lock);
	if (pkcs12 == NULL)
	{
		// Failure
		return NULL;
	}

	return PKCS12ToP12(pkcs12);
}