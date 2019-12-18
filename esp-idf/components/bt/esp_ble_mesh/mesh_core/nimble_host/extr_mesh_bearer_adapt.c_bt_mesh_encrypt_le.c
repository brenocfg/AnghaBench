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
typedef  int /*<<< orphan*/  const u8_t ;
struct tc_aes_key_sched_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,...) ; 
 int EINVAL ; 
 scalar_t__ TC_CRYPTO_FAIL ; 
 int /*<<< orphan*/  bt_hex (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ecb_encrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_mem_swap (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  sys_memcpy_swap (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ tc_aes128_set_encrypt_key (struct tc_aes_key_sched_struct*,int /*<<< orphan*/  const*) ; 
 scalar_t__ tc_aes_encrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct tc_aes_key_sched_struct*) ; 

int bt_mesh_encrypt_le(const u8_t key[16], const u8_t plaintext[16],
                       u8_t enc_data[16])
{
#if CONFIG_MBEDTLS_HARDWARE_AES
    BT_DBG("key %s plaintext %s", bt_hex(key, 16), bt_hex(plaintext, 16));

    ecb_encrypt(key, plaintext, enc_data, NULL);

    BT_DBG("enc_data %s", bt_hex(enc_data, 16));
    return 0;
#else /* CONFIG_MBEDTLS_HARDWARE_AES */
    struct tc_aes_key_sched_struct s;
    u8_t tmp[16];

    BT_DBG("key %s plaintext %s", bt_hex(key, 16), bt_hex(plaintext, 16));

    sys_memcpy_swap(tmp, key, 16);

    if (tc_aes128_set_encrypt_key(&s, tmp) == TC_CRYPTO_FAIL) {
        return -EINVAL;
    }

    sys_memcpy_swap(tmp, plaintext, 16);

    if (tc_aes_encrypt(enc_data, tmp, &s) == TC_CRYPTO_FAIL) {
        return -EINVAL;
    }

    sys_mem_swap(enc_data, 16);

    BT_DBG("enc_data %s", bt_hex(enc_data, 16));

    return 0;
#endif /* CONFIG_MBEDTLS_HARDWARE_AES */
}