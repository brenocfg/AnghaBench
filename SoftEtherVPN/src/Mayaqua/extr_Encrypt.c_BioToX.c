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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509ToX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_X509_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  openssl_lock ; 

X *BioToX(BIO *bio, bool text)
{
	X *x;
	X509 *x509;
	// Validate arguments
	if (bio == NULL)
	{
		return NULL;
	}

	Lock(openssl_lock);
	{
		// Reading x509
		if (text == false)
		{
			// Binary mode
			x509 = d2i_X509_bio(bio, NULL);
		}
		else
		{
			// Text mode
			x509 = PEM_read_bio_X509(bio, NULL, NULL, NULL);
		}
	}
	Unlock(openssl_lock);

	if (x509 == NULL)
	{
		return NULL;
	}

	x = X509ToX(x509);

	if (x == NULL)
	{
		return NULL;
	}

	return x;
}