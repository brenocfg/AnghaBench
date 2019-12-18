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
struct cryptocop_transform_init {int alg; int keylen; int /*<<< orphan*/  cipher_mode; int /*<<< orphan*/  csum_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_API (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  cryptocop_alg_3des 137 
#define  cryptocop_alg_aes 136 
#define  cryptocop_alg_csum 135 
#define  cryptocop_alg_des 134 
#define  cryptocop_alg_md5 133 
#define  cryptocop_alg_mem2mem 132 
#define  cryptocop_alg_sha1 131 
 int /*<<< orphan*/  cryptocop_cipher_mode_cbc ; 
 int /*<<< orphan*/  cryptocop_cipher_mode_ecb ; 
#define  cryptocop_csum_be 130 
#define  cryptocop_csum_le 129 
#define  cryptocop_no_alg 128 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int transform_ok(struct cryptocop_transform_init *tinit)
{
	switch (tinit->alg){
	case cryptocop_alg_csum:
		switch (tinit->csum_mode){
		case cryptocop_csum_le:
		case cryptocop_csum_be:
			break;
		default:
			DEBUG_API(printk("transform_ok: Bad mode set for csum transform\n"));
			return -EINVAL;
		}
	case cryptocop_alg_mem2mem:
	case cryptocop_alg_md5:
	case cryptocop_alg_sha1:
		if (tinit->keylen != 0) {
			DEBUG_API(printk("transform_ok: non-zero keylength, %d, for a digest/csum algorithm\n", tinit->keylen));
			return -EINVAL; /* This check is a bit strict. */
		}
		break;
	case cryptocop_alg_des:
		if (tinit->keylen != 64) {
			DEBUG_API(printk("transform_ok: keylen %d invalid for DES\n", tinit->keylen));
			return -EINVAL;
		}
		break;
	case cryptocop_alg_3des:
		if (tinit->keylen != 192) {
			DEBUG_API(printk("transform_ok: keylen %d invalid for 3DES\n", tinit->keylen));
			return -EINVAL;
		}
		break;
	case cryptocop_alg_aes:
		if (tinit->keylen != 128 && tinit->keylen != 192 && tinit->keylen != 256) {
			DEBUG_API(printk("transform_ok: keylen %d invalid for AES\n", tinit->keylen));
			return -EINVAL;
		}
		break;
	case cryptocop_no_alg:
	default:
		DEBUG_API(printk("transform_ok: no such algorithm %d\n", tinit->alg));
		return -EINVAL;
	}

	switch (tinit->alg){
	case cryptocop_alg_des:
	case cryptocop_alg_3des:
	case cryptocop_alg_aes:
		if (tinit->cipher_mode != cryptocop_cipher_mode_ecb && tinit->cipher_mode != cryptocop_cipher_mode_cbc) return -EINVAL;
	default:
		 break;
	}
	return 0;
}