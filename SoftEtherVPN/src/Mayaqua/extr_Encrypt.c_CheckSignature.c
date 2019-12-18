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
struct TYPE_5__ {int /*<<< orphan*/  x509; } ;
typedef  TYPE_1__ X ;
struct TYPE_6__ {int /*<<< orphan*/  pkey; } ;
typedef  TYPE_2__ K ;

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ X509_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openssl_lock ; 

bool CheckSignature(X *x, K *k)
{
	// Validate arguments
	if (x == NULL || k == NULL)
	{
		return false;
	}

	Lock(openssl_lock);
	{
		if (X509_verify(x->x509, k->pkey) == 0)
		{
			Unlock(openssl_lock);
			return false;
		}
	}
	Unlock(openssl_lock);
	return true;
}