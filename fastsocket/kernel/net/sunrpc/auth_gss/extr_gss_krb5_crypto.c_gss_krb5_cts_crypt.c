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
typedef  int u32 ;
struct xdr_buf {int len; struct page** pages; } ;
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
struct crypto_blkcipher {int dummy; } ;
struct blkcipher_desc {int /*<<< orphan*/ * info; struct crypto_blkcipher* tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int crypto_blkcipher_blocksize (struct crypto_blkcipher*) ; 
 int crypto_blkcipher_decrypt_iv (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,int) ; 
 int crypto_blkcipher_encrypt_iv (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,int) ; 
 int read_bytes_from_xdr_buf (struct xdr_buf*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,int) ; 
 int write_bytes_to_xdr_buf (struct xdr_buf*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u32
gss_krb5_cts_crypt(struct crypto_blkcipher *cipher, struct xdr_buf *buf,
		   u32 offset, u8 *iv, struct page **pages, int encrypt)
{
	u32 ret;
	struct scatterlist sg[1];
	struct blkcipher_desc desc = { .tfm = cipher, .info = iv };
	u8 data[crypto_blkcipher_blocksize(cipher) * 2];
	struct page **save_pages;
	u32 len = buf->len - offset;

	BUG_ON(len > crypto_blkcipher_blocksize(cipher) * 2);

	/*
	 * For encryption, we want to read from the cleartext
	 * page cache pages, and write the encrypted data to
	 * the supplied xdr_buf pages.
	 */
	save_pages = buf->pages;
	if (encrypt)
		buf->pages = pages;

	ret = read_bytes_from_xdr_buf(buf, offset, data, len);
	buf->pages = save_pages;
	if (ret)
		goto out;

	sg_init_one(sg, data, len);

	if (encrypt)
		ret = crypto_blkcipher_encrypt_iv(&desc, sg, sg, len);
	else
		ret = crypto_blkcipher_decrypt_iv(&desc, sg, sg, len);

	if (ret)
		goto out;

	ret = write_bytes_to_xdr_buf(buf, offset, data, len);

out:
	return ret;
}