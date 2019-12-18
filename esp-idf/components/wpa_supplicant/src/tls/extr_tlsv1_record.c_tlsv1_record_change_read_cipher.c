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
struct tlsv1_record_layer {scalar_t__ cipher_alg; int /*<<< orphan*/ * read_cbc; int /*<<< orphan*/  key_material_len; int /*<<< orphan*/  read_key; int /*<<< orphan*/  read_iv; int /*<<< orphan*/  read_seq_num; int /*<<< orphan*/  cipher_suite; int /*<<< orphan*/  read_cipher_suite; } ;

/* Variables and functions */
 scalar_t__ CRYPTO_CIPHER_NULL ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TLS_SEQ_NUM_LEN ; 
 int /*<<< orphan*/  crypto_cipher_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * crypto_cipher_init (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int tlsv1_record_change_read_cipher(struct tlsv1_record_layer *rl)
{
	wpa_printf(MSG_DEBUG, "TLSv1: Record Layer - New read cipher suite "
		   "0x%04x \n", rl->cipher_suite);
	rl->read_cipher_suite = rl->cipher_suite;
	os_memset(rl->read_seq_num, 0, TLS_SEQ_NUM_LEN);

	if (rl->read_cbc) {
		crypto_cipher_deinit(rl->read_cbc);
		rl->read_cbc =  NULL;
	}

	if (rl->cipher_alg != CRYPTO_CIPHER_NULL) {
		rl->read_cbc = crypto_cipher_init(rl->cipher_alg,
									rl->read_iv, rl->read_key,
									rl->key_material_len);
		if (rl->read_cbc == NULL) {
			wpa_printf(MSG_DEBUG, "TLSv1: Failed to initialize "
				   "cipher");
			return -1;
		}
	}

	return 0;
}