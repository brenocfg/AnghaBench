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
struct loop_info64 {int lo_offset; int /*<<< orphan*/  lo_encrypt_key_size; int /*<<< orphan*/  lo_encrypt_key; int /*<<< orphan*/  lo_crypt_name; } ;
struct loop_device {struct crypto_blkcipher* key_data; } ;
struct crypto_blkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct crypto_blkcipher*) ; 
 int LOOP_IV_SECTOR_SIZE ; 
 int LO_NAME_SIZE ; 
 int PTR_ERR (struct crypto_blkcipher*) ; 
 struct crypto_blkcipher* crypto_alloc_blkcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_blkcipher_setkey (struct crypto_blkcipher*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_blkcipher (struct crypto_blkcipher*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int strcspn (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cryptoloop_init(struct loop_device *lo, const struct loop_info64 *info)
{
	int err = -EINVAL;
	int cipher_len;
	int mode_len;
	char cms[LO_NAME_SIZE];			/* cipher-mode string */
	char *cipher;
	char *mode;
	char *cmsp = cms;			/* c-m string pointer */
	struct crypto_blkcipher *tfm;

	/* encryption breaks for non sector aligned offsets */

	if (info->lo_offset % LOOP_IV_SECTOR_SIZE)
		goto out;

	strncpy(cms, info->lo_crypt_name, LO_NAME_SIZE);
	cms[LO_NAME_SIZE - 1] = 0;

	cipher = cmsp;
	cipher_len = strcspn(cmsp, "-");

	mode = cmsp + cipher_len;
	mode_len = 0;
	if (*mode) {
		mode++;
		mode_len = strcspn(mode, "-");
	}

	if (!mode_len) {
		mode = "cbc";
		mode_len = 3;
	}

	if (cipher_len + mode_len + 3 > LO_NAME_SIZE)
		return -EINVAL;

	memmove(cms, mode, mode_len);
	cmsp = cms + mode_len;
	*cmsp++ = '(';
	memcpy(cmsp, info->lo_crypt_name, cipher_len);
	cmsp += cipher_len;
	*cmsp++ = ')';
	*cmsp = 0;

	tfm = crypto_alloc_blkcipher(cms, 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(tfm))
		return PTR_ERR(tfm);

	err = crypto_blkcipher_setkey(tfm, info->lo_encrypt_key,
				      info->lo_encrypt_key_size);
	
	if (err != 0)
		goto out_free_tfm;

	lo->key_data = tfm;
	return 0;

 out_free_tfm:
	crypto_free_blkcipher(tfm);

 out:
	return err;
}