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
struct scatterlist {int dummy; } ;
struct crypto_cts_ctx {int /*<<< orphan*/  child; } ;
struct blkcipher_desc {int /*<<< orphan*/ * info; int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm; } ;
typedef  int /*<<< orphan*/  s ;

/* Variables and functions */
 int EINVAL ; 
 int crypto_blkcipher_blocksize (int /*<<< orphan*/ ) ; 
 int crypto_blkcipher_encrypt_iv (struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,struct scatterlist*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cts_cbc_encrypt(struct crypto_cts_ctx *ctx,
			   struct blkcipher_desc *desc,
			   struct scatterlist *dst,
			   struct scatterlist *src,
			   unsigned int offset,
			   unsigned int nbytes)
{
	int bsize = crypto_blkcipher_blocksize(desc->tfm);
	u8 tmp[bsize], tmp2[bsize];
	struct blkcipher_desc lcldesc;
	struct scatterlist sgsrc[1], sgdst[1];
	int lastn = nbytes - bsize;
	u8 iv[bsize];
	u8 s[bsize * 2], d[bsize * 2];
	int err;

	if (lastn < 0)
		return -EINVAL;

	sg_init_table(sgsrc, 1);
	sg_init_table(sgdst, 1);

	memset(s, 0, sizeof(s));
	scatterwalk_map_and_copy(s, src, offset, nbytes, 0);

	memcpy(iv, desc->info, bsize);

	lcldesc.tfm = ctx->child;
	lcldesc.info = iv;
	lcldesc.flags = desc->flags;

	sg_set_buf(&sgsrc[0], s, bsize);
	sg_set_buf(&sgdst[0], tmp, bsize);
	err = crypto_blkcipher_encrypt_iv(&lcldesc, sgdst, sgsrc, bsize);

	memcpy(d + bsize, tmp, lastn);

	lcldesc.info = tmp;

	sg_set_buf(&sgsrc[0], s + bsize, bsize);
	sg_set_buf(&sgdst[0], tmp2, bsize);
	err = crypto_blkcipher_encrypt_iv(&lcldesc, sgdst, sgsrc, bsize);

	memcpy(d, tmp2, bsize);

	scatterwalk_map_and_copy(d, dst, offset, nbytes, 1);

	memcpy(desc->info, tmp2, bsize);

	return err;
}