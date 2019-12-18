#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* Ctx; scalar_t__ IsHMac; } ;
typedef  TYPE_1__ MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  HMAC_CTX_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  HMAC_CTX_free (TYPE_1__*) ; 

void FreeMd(MD *md)
{
	// Validate arguments
	if (md == NULL)
	{
		return;
	}

	if (md->Ctx != NULL)
	{
		if (md->IsHMac)
		{
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
			HMAC_CTX_free(md->Ctx);
#else
			HMAC_CTX_cleanup(md->Ctx);
			Free(md->Ctx);
#endif
		}
		else
		{
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
			EVP_MD_CTX_free(md->Ctx);
#else
			EVP_MD_CTX_destroy(md->Ctx);
#endif
		}
	}

	Free(md);
}