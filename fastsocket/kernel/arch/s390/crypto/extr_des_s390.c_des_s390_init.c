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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int CRYPT_S390_MSA ; 
 int CRYPT_S390_MSA4 ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KMCTR_DEA_ENCRYPT ; 
 int /*<<< orphan*/  KMCTR_TDEA_192_ENCRYPT ; 
 int /*<<< orphan*/  KM_DEA_ENCRYPT ; 
 int /*<<< orphan*/  KM_TDEA_128_ENCRYPT ; 
 int /*<<< orphan*/  KM_TDEA_192_ENCRYPT ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbc_des3_128_alg ; 
 int /*<<< orphan*/  cbc_des3_192_alg ; 
 int /*<<< orphan*/  cbc_des_alg ; 
 scalar_t__ crypt_s390_func_available (int /*<<< orphan*/ ,int) ; 
 int crypto_register_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctr_des3_alg ; 
 int /*<<< orphan*/  ctr_des_alg ; 
 int /*<<< orphan*/ * ctrblk ; 
 int /*<<< orphan*/  des3_128_alg ; 
 int /*<<< orphan*/  des3_192_alg ; 
 int /*<<< orphan*/  des_alg ; 
 int /*<<< orphan*/  ecb_des3_128_alg ; 
 int /*<<< orphan*/  ecb_des3_192_alg ; 
 int /*<<< orphan*/  ecb_des_alg ; 

__attribute__((used)) static int des_s390_init(void)
{
	int ret = 0;

	if (!crypt_s390_func_available(KM_DEA_ENCRYPT, CRYPT_S390_MSA) ||
	    !crypt_s390_func_available(KM_TDEA_128_ENCRYPT, CRYPT_S390_MSA) ||
	    !crypt_s390_func_available(KM_TDEA_192_ENCRYPT, CRYPT_S390_MSA))
		return -EOPNOTSUPP;

	ret = crypto_register_alg(&des_alg);
	if (ret)
		goto des_err;
	ret = crypto_register_alg(&ecb_des_alg);
	if (ret)
		goto ecb_des_err;
	ret = crypto_register_alg(&cbc_des_alg);
	if (ret)
		goto cbc_des_err;

	ret = crypto_register_alg(&des3_128_alg);
	if (ret)
		goto des3_128_err;
	ret = crypto_register_alg(&ecb_des3_128_alg);
	if (ret)
		goto ecb_des3_128_err;
	ret = crypto_register_alg(&cbc_des3_128_alg);
	if (ret)
		goto cbc_des3_128_err;

	ret = crypto_register_alg(&des3_192_alg);
	if (ret)
		goto des3_192_err;
	ret = crypto_register_alg(&ecb_des3_192_alg);
	if (ret)
		goto ecb_des3_192_err;
	ret = crypto_register_alg(&cbc_des3_192_alg);
	if (ret)
		goto cbc_des3_192_err;

	if (crypt_s390_func_available(KMCTR_DEA_ENCRYPT,
			CRYPT_S390_MSA | CRYPT_S390_MSA4) &&
	    crypt_s390_func_available(KMCTR_TDEA_192_ENCRYPT,
			CRYPT_S390_MSA | CRYPT_S390_MSA4)) {
		ret = crypto_register_alg(&ctr_des_alg);
		if (ret)
			goto ctr_des_err;
		ret = crypto_register_alg(&ctr_des3_alg);
		if (ret)
			goto ctr_des3_err;
		ctrblk = (u8 *) __get_free_page(GFP_KERNEL);
		if (!ctrblk) {
			ret = -ENOMEM;
			goto ctr_mem_err;
		}
	}

out:
	return ret;

ctr_mem_err:
	crypto_unregister_alg(&ctr_des3_alg);
ctr_des3_err:
	crypto_unregister_alg(&ctr_des_alg);
ctr_des_err:
	crypto_unregister_alg(&cbc_des3_192_alg);
cbc_des3_192_err:
	crypto_unregister_alg(&ecb_des3_192_alg);
ecb_des3_192_err:
	crypto_unregister_alg(&des3_192_alg);
des3_192_err:
	crypto_unregister_alg(&cbc_des3_128_alg);
cbc_des3_128_err:
	crypto_unregister_alg(&ecb_des3_128_alg);
ecb_des3_128_err:
	crypto_unregister_alg(&des3_128_alg);
des3_128_err:
	crypto_unregister_alg(&cbc_des_alg);
cbc_des_err:
	crypto_unregister_alg(&ecb_des_alg);
ecb_des_err:
	crypto_unregister_alg(&des_alg);
des_err:
	goto out;
}