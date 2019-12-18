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
typedef  int uint8_t ;
struct TYPE_3__ {int* words; } ;
typedef  TYPE_1__* TCAesKeySched_t ;

/* Variables and functions */
 unsigned int Nb ; 
 unsigned int Nk ; 
 int Nr ; 
 int TC_CRYPTO_FAIL ; 
 int TC_CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  rotword (unsigned int) ; 
 unsigned int const subword (int /*<<< orphan*/ ) ; 

int tc_aes128_set_encrypt_key(TCAesKeySched_t s, const uint8_t *k)
{
    const unsigned int rconst[11] = {
        0x00000000, 0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000,
        0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000
    };
    unsigned int i;
    unsigned int t;

    if (s == (TCAesKeySched_t) 0) {
        return TC_CRYPTO_FAIL;
    } else if (k == (const uint8_t *) 0) {
        return TC_CRYPTO_FAIL;
    }

    for (i = 0; i < Nk; ++i) {
        s->words[i] = (k[Nb * i] << 24) | (k[Nb * i + 1] << 16) |
                      (k[Nb * i + 2] << 8) | (k[Nb * i + 3]);
    }

    for (; i < (Nb * (Nr + 1)); ++i) {
        t = s->words[i - 1];
        if ((i % Nk) == 0) {
            t = subword(rotword(t)) ^ rconst[i / Nk];
        }
        s->words[i] = s->words[i - Nk] ^ t;
    }

    return TC_CRYPTO_SUCCESS;
}