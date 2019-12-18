#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* Ctx; } ;
typedef  TYPE_1__ CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 

void FreeCipher(CIPHER *c)
{
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	if (c->Ctx != NULL)
	{
#if OPENSSL_VERSION_NUMBER >= 0x10100000L
		EVP_CIPHER_CTX_free(c->Ctx);
#else
		EVP_CIPHER_CTX_cleanup(c->Ctx);
		Free(c->Ctx);
#endif
	}

	Free(c);
}