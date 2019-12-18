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
struct TYPE_3__ {int /*<<< orphan*/  hmac; int /*<<< orphan*/  aes; } ;
typedef  TYPE_1__ mz_stream_wzaes ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  mz_crypt_aes_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_crypt_hmac_delete (int /*<<< orphan*/ *) ; 

void mz_stream_wzaes_delete(void **stream)
{
    mz_stream_wzaes *wzaes = NULL;
    if (stream == NULL)
        return;
    wzaes = (mz_stream_wzaes *)*stream;
    if (wzaes != NULL)
    {
        mz_crypt_aes_delete(&wzaes->aes);
        mz_crypt_hmac_delete(&wzaes->hmac);
        MZ_FREE(wzaes);
    }
    *stream = NULL;
}