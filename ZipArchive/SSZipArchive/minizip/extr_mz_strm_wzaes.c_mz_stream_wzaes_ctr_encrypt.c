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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ crypt_pos; int /*<<< orphan*/ * crypt_block; int /*<<< orphan*/  aes; int /*<<< orphan*/ * nonce; } ;
typedef  TYPE_1__ mz_stream_wzaes ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_AES_BLOCK_SIZE ; 
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mz_crypt_aes_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int32_t mz_stream_wzaes_ctr_encrypt(void *stream, uint8_t *buf, int32_t size)
{
    mz_stream_wzaes *wzaes = (mz_stream_wzaes *)stream;
    uint32_t pos = wzaes->crypt_pos;
    uint32_t i = 0;
    int32_t err = MZ_OK;

    while (i < (uint32_t)size)
    {
        if (pos == MZ_AES_BLOCK_SIZE)
        {
            uint32_t j = 0;

            /* Increment encryption nonce */
            while (j < 8 && !++wzaes->nonce[j])
                j += 1;

            /* Encrypt the nonce to form next xor buffer */
            memcpy(wzaes->crypt_block, wzaes->nonce, MZ_AES_BLOCK_SIZE);
            mz_crypt_aes_encrypt(wzaes->aes, wzaes->crypt_block, sizeof(wzaes->crypt_block));
            pos = 0;
        }

        buf[i++] ^= wzaes->crypt_block[pos++];
    }

    wzaes->crypt_pos = pos;
    return err;
}