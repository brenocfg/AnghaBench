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
struct TYPE_3__ {int /*<<< orphan*/  pkcs12; } ;
typedef  TYPE_1__ P12 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewBio () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2d_PKCS12_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openssl_lock ; 

BIO *P12ToBio(P12 *p12)
{
	BIO *bio;
	// Validate arguments
	if (p12 == NULL)
	{
		return NULL;
	}

	bio = NewBio();
	Lock(openssl_lock);
	{
		i2d_PKCS12_bio(bio, p12->pkcs12);
	}
	Unlock(openssl_lock);

	return bio;
}