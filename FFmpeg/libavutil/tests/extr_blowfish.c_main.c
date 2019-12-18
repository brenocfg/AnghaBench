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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  AVBlowfish ;

/* Variables and functions */
 scalar_t__* IV ; 
 int NUM_VARIABLE_KEY_TESTS ; 
 int /*<<< orphan*/ * av_blowfish_alloc () ; 
 int /*<<< orphan*/  av_blowfish_crypt_ecb (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  av_blowfish_init (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 scalar_t__* ciphertext ; 
 scalar_t__* ciphertext2 ; 
 scalar_t__* ciphertext_l ; 
 scalar_t__* ciphertext_r ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__* plaintext ; 
 scalar_t__* plaintext2 ; 
 scalar_t__* plaintext_l ; 
 scalar_t__* plaintext_r ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_blowfish (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,int,scalar_t__*,int,char*) ; 
 char** variable_key ; 

int main(void)
{
    uint32_t tmptext_l[NUM_VARIABLE_KEY_TESTS];
    uint32_t tmptext_r[NUM_VARIABLE_KEY_TESTS];
    uint8_t tmp[16], iv[8];
    int i;
    AVBlowfish *ctx = av_blowfish_alloc();
    if (!ctx)
        return 1;

    av_blowfish_init(ctx, "abcdefghijklmnopqrstuvwxyz", 26);

    test_blowfish(ctx, tmp, plaintext, ciphertext, 1, NULL, 0, "encryption");
    test_blowfish(ctx, tmp, ciphertext, plaintext, 1, NULL, 1, "decryption");
    test_blowfish(ctx, tmp, tmp, ciphertext, 1, NULL, 0, "Inplace encryption");
    test_blowfish(ctx, tmp, tmp, plaintext,  1, NULL, 1, "Inplace decryption");
    memcpy(iv, IV, 8);
    test_blowfish(ctx, tmp, plaintext2, ciphertext2, 2, iv, 0, "CBC encryption");
    memcpy(iv, IV, 8);
    test_blowfish(ctx, tmp, ciphertext2, plaintext2, 2, iv, 1, "CBC decryption");
    memcpy(iv, IV, 8);
    test_blowfish(ctx, tmp, tmp, ciphertext2, 2, iv, 0, "Inplace CBC encryption");
    memcpy(iv, IV, 8);
    test_blowfish(ctx, tmp, tmp, plaintext2,  2, iv, 1, "Inplace CBC decryption");

    memcpy(tmptext_l, plaintext_l, sizeof(*plaintext_l) * NUM_VARIABLE_KEY_TESTS);
    memcpy(tmptext_r, plaintext_r, sizeof(*plaintext_r) * NUM_VARIABLE_KEY_TESTS);

    for (i = 0; i < NUM_VARIABLE_KEY_TESTS; i++) {
        av_blowfish_init(ctx, variable_key[i], 8);

        av_blowfish_crypt_ecb(ctx, &tmptext_l[i], &tmptext_r[i], 0);
        if (tmptext_l[i] != ciphertext_l[i] || tmptext_r[i] != ciphertext_r[i]) {
            printf("Test encryption failed.\n");
            return 2;
        }

        av_blowfish_crypt_ecb(ctx, &tmptext_l[i], &tmptext_r[i], 1);
        if (tmptext_l[i] != plaintext_l[i] || tmptext_r[i] != plaintext_r[i]) {
            printf("Test decryption failed.\n");
            return 3;
        }
    }
    printf("Test encryption/decryption success.\n");
    av_free(ctx);

    return 0;
}