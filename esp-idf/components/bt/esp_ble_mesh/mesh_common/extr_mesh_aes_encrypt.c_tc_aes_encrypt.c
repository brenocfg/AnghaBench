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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  state ;
struct TYPE_3__ {scalar_t__ words; } ;
typedef  TYPE_1__* const TCAesKeySched_t ;

/* Variables and functions */
 int Nb ; 
 int Nk ; 
 int Nr ; 
 int TC_CRYPTO_FAIL ; 
 int TC_CRYPTO_SUCCESS ; 
 int /*<<< orphan*/  TC_ZERO_BYTE ; 
 int /*<<< orphan*/  _copy (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  _set (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_round_key (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  mix_columns (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  shift_rows (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sub_bytes (int /*<<< orphan*/  const*) ; 

int tc_aes_encrypt(uint8_t *out, const uint8_t *in, const TCAesKeySched_t s)
{
    uint8_t state[Nk * Nb];
    unsigned int i;

    if (out == (uint8_t *) 0) {
        return TC_CRYPTO_FAIL;
    } else if (in == (const uint8_t *) 0) {
        return TC_CRYPTO_FAIL;
    } else if (s == (TCAesKeySched_t) 0) {
        return TC_CRYPTO_FAIL;
    }

    (void)_copy(state, sizeof(state), in, sizeof(state));
    add_round_key(state, s->words);

    for (i = 0; i < (Nr - 1); ++i) {
        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, s->words + Nb * (i + 1));
    }

    sub_bytes(state);
    shift_rows(state);
    add_round_key(state, s->words + Nb * (i + 1));

    (void)_copy(out, sizeof(state), state, sizeof(state));

    /* zeroing out the state buffer */
    _set(state, TC_ZERO_BYTE, sizeof(state));

    return TC_CRYPTO_SUCCESS;
}