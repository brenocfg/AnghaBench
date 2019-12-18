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
struct scatterlist {int dummy; } ;
struct ecryptfs_crypt_stat {int /*<<< orphan*/  cs_tfm_mutex; int /*<<< orphan*/  key_size; int /*<<< orphan*/  key; int /*<<< orphan*/  tfm; } ;
struct blkcipher_desc {unsigned char* info; int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int crypto_blkcipher_decrypt_iv (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,int) ; 
 int crypto_blkcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decrypt_scatterlist(struct ecryptfs_crypt_stat *crypt_stat,
			       struct scatterlist *dest_sg,
			       struct scatterlist *src_sg, int size,
			       unsigned char *iv)
{
	struct blkcipher_desc desc = {
		.tfm = crypt_stat->tfm,
		.info = iv,
		.flags = CRYPTO_TFM_REQ_MAY_SLEEP
	};
	int rc = 0;

	/* Consider doing this once, when the file is opened */
	mutex_lock(&crypt_stat->cs_tfm_mutex);
	rc = crypto_blkcipher_setkey(crypt_stat->tfm, crypt_stat->key,
				     crypt_stat->key_size);
	if (rc) {
		ecryptfs_printk(KERN_ERR, "Error setting key; rc = [%d]\n",
				rc);
		mutex_unlock(&crypt_stat->cs_tfm_mutex);
		rc = -EINVAL;
		goto out;
	}
	ecryptfs_printk(KERN_DEBUG, "Decrypting [%d] bytes.\n", size);
	rc = crypto_blkcipher_decrypt_iv(&desc, dest_sg, src_sg, size);
	mutex_unlock(&crypt_stat->cs_tfm_mutex);
	if (rc) {
		ecryptfs_printk(KERN_ERR, "Error decrypting; rc = [%d]\n",
				rc);
		goto out;
	}
	rc = size;
out:
	return rc;
}