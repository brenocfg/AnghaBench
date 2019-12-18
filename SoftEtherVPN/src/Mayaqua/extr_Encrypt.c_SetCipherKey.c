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
struct TYPE_3__ {int IsNullCipher; int Encrypt; int /*<<< orphan*/  Cipher; int /*<<< orphan*/ * Ctx; } ;
typedef  TYPE_1__ CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CipherInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int) ; 

void SetCipherKey(CIPHER *c, void *key, bool enc)
{
	// Validate arguments
	if (c == NULL || key == NULL)
	{
		return;
	}

	if (c->IsNullCipher == false)
	{
		if (c->Ctx != NULL)
		{
			EVP_CipherInit(c->Ctx, c->Cipher, key, NULL, enc);
		}
	}

	c->Encrypt = enc;
}