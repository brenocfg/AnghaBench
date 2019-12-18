#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct crypt_s390_des_ctx {int /*<<< orphan*/  key; } ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; int /*<<< orphan*/ * iv; TYPE_4__ src; TYPE_2__ dst; } ;
struct blkcipher_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DES_BLOCK_SIZE ; 
 unsigned int PAGE_SIZE ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int blkcipher_walk_virt_block (struct blkcipher_desc*,struct blkcipher_walk*,int) ; 
 int crypt_s390_kmctr (long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_inc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ctrblk ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ctr_desall_crypt(struct blkcipher_desc *desc, long func,
			    struct crypt_s390_des_ctx *ctx, struct blkcipher_walk *walk)
{
	int ret = blkcipher_walk_virt_block(desc, walk, DES_BLOCK_SIZE);
	unsigned int i, n, nbytes;
	u8 buf[DES_BLOCK_SIZE];
	u8 *out, *in;

	memcpy(ctrblk, walk->iv, DES_BLOCK_SIZE);
	while ((nbytes = walk->nbytes) >= DES_BLOCK_SIZE) {
		out = walk->dst.virt.addr;
		in = walk->src.virt.addr;
		while (nbytes >= DES_BLOCK_SIZE) {
			/* align to block size, max. PAGE_SIZE */
			n = (nbytes > PAGE_SIZE) ? PAGE_SIZE :
				nbytes & ~(DES_BLOCK_SIZE - 1);
			for (i = DES_BLOCK_SIZE; i < n; i += DES_BLOCK_SIZE) {
				memcpy(ctrblk + i, ctrblk + i - DES_BLOCK_SIZE,
				       DES_BLOCK_SIZE);
				crypto_inc(ctrblk + i, DES_BLOCK_SIZE);
			}
			ret = crypt_s390_kmctr(func, ctx->key, out, in, n, ctrblk);
			BUG_ON((ret < 0) || (ret != n));
			if (n > DES_BLOCK_SIZE)
				memcpy(ctrblk, ctrblk + n - DES_BLOCK_SIZE,
				       DES_BLOCK_SIZE);
			crypto_inc(ctrblk, DES_BLOCK_SIZE);
			out += n;
			in += n;
			nbytes -= n;
		}
		ret = blkcipher_walk_done(desc, walk, nbytes);
	}

	/* final block may be < DES_BLOCK_SIZE, copy only nbytes */
	if (nbytes) {
		out = walk->dst.virt.addr;
		in = walk->src.virt.addr;
		ret = crypt_s390_kmctr(func, ctx->key, buf, in,
				       DES_BLOCK_SIZE, ctrblk);
		BUG_ON(ret < 0 || ret != DES_BLOCK_SIZE);
		memcpy(out, buf, nbytes);
		crypto_inc(ctrblk, DES_BLOCK_SIZE);
		ret = blkcipher_walk_done(desc, walk, 0);
	}
	memcpy(walk->iv, ctrblk, DES_BLOCK_SIZE);
	return ret;
}