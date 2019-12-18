#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * crypt; } ;
typedef  TYPE_1__ mz_crypt_aes ;

/* Variables and functions */
 int /*<<< orphan*/  CCCryptorRelease (int /*<<< orphan*/ *) ; 

void mz_crypt_aes_reset(void *handle)
{
    mz_crypt_aes *aes = (mz_crypt_aes *)handle;

    if (aes->crypt != NULL)
        CCCryptorRelease(aes->crypt);
    aes->crypt = NULL;
}