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
struct TYPE_3__ {int /*<<< orphan*/  x509; } ;
typedef  TYPE_1__ X ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewBio () ; 
 int /*<<< orphan*/  PEM_write_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2d_X509_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openssl_lock ; 

BIO *XToBio(X *x, bool text)
{
	BIO *bio;
	// Validate arguments
	if (x == NULL)
	{
		return NULL;
	}

	bio = NewBio();

	Lock(openssl_lock);
	{
		if (text == false)
		{
			// Binary format
			i2d_X509_bio(bio, x->x509);
		}
		else
		{
			// Text format
			PEM_write_bio_X509(bio, x->x509);
		}
	}
	Unlock(openssl_lock);

	return bio;
}