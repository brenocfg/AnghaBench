#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  xts; void* key; int /*<<< orphan*/  tweak; int /*<<< orphan*/  bit; int /*<<< orphan*/  block; } ;
struct s390_xts_ctx {int key_len; void* key; TYPE_1__ pcc; int /*<<< orphan*/  xts_param; } ;
struct TYPE_9__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_10__ {TYPE_4__ virt; } ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_2__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; TYPE_5__ src; TYPE_3__ dst; int /*<<< orphan*/  iv; } ;
struct blkcipher_desc {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 int crypt_s390_km (long,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int crypt_s390_pcc (long,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xts_aes_crypt(struct blkcipher_desc *desc, long func,
			 struct s390_xts_ctx *xts_ctx,
			 struct blkcipher_walk *walk)
{
	unsigned int offset = (xts_ctx->key_len >> 1) & 0x10;
	int ret = blkcipher_walk_virt(desc, walk);
	unsigned int nbytes = walk->nbytes;
	unsigned int n;
	u8 *in, *out;
	void *param;

	if (!nbytes)
		goto out;

	memset(xts_ctx->pcc.block, 0, sizeof(xts_ctx->pcc.block));
	memset(xts_ctx->pcc.bit, 0, sizeof(xts_ctx->pcc.bit));
	memset(xts_ctx->pcc.xts, 0, sizeof(xts_ctx->pcc.xts));
	memcpy(xts_ctx->pcc.tweak, walk->iv, sizeof(xts_ctx->pcc.tweak));
	param = xts_ctx->pcc.key + offset;
	ret = crypt_s390_pcc(func, param);
	BUG_ON(ret < 0);

	memcpy(xts_ctx->xts_param, xts_ctx->pcc.xts, 16);
	param = xts_ctx->key + offset;
	do {
		/* only use complete blocks */
		n = nbytes & ~(AES_BLOCK_SIZE - 1);
		out = walk->dst.virt.addr;
		in = walk->src.virt.addr;

		ret = crypt_s390_km(func, param, out, in, n);
		BUG_ON(ret < 0 || ret != n);

		nbytes &= AES_BLOCK_SIZE - 1;
		ret = blkcipher_walk_done(desc, walk, nbytes);
	} while ((nbytes = walk->nbytes));
out:
	return ret;
}