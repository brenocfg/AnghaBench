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
struct scatterlist {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {TYPE_3__ virt; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; int /*<<< orphan*/  iv; TYPE_4__ dst; TYPE_2__ src; } ;
struct blkcipher_desc {int /*<<< orphan*/  tfm; } ;
struct TYPE_10__ {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; } ;
struct aes_ctx {TYPE_5__ cword; int /*<<< orphan*/  E; } ;

/* Variables and functions */
 unsigned int AES_BLOCK_SIZE ; 
 struct aes_ctx* blk_aes_ctx (int /*<<< orphan*/ ) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 int /*<<< orphan*/  irq_ts_restore (int) ; 
 int irq_ts_save () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  padlock_reset_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  padlock_store_cword (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * padlock_xcrypt_cbc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int cbc_aes_encrypt(struct blkcipher_desc *desc,
			   struct scatterlist *dst, struct scatterlist *src,
			   unsigned int nbytes)
{
	struct aes_ctx *ctx = blk_aes_ctx(desc->tfm);
	struct blkcipher_walk walk;
	int err;
	int ts_state;

	padlock_reset_key(&ctx->cword.encrypt);

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	ts_state = irq_ts_save();
	while ((nbytes = walk.nbytes)) {
		u8 *iv = padlock_xcrypt_cbc(walk.src.virt.addr,
					    walk.dst.virt.addr, ctx->E,
					    walk.iv, &ctx->cword.encrypt,
					    nbytes / AES_BLOCK_SIZE);
		memcpy(walk.iv, iv, AES_BLOCK_SIZE);
		nbytes &= AES_BLOCK_SIZE - 1;
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}
	irq_ts_restore(ts_state);

	padlock_store_cword(&ctx->cword.decrypt);

	return err;
}