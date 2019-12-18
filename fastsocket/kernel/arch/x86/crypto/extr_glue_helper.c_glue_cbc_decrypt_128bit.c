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
struct common_glue_ctx {int /*<<< orphan*/  fpu_blocks_limit; } ;
struct blkcipher_walk {unsigned int nbytes; } ;
struct blkcipher_desc {int dummy; } ;

/* Variables and functions */
 unsigned int __glue_cbc_decrypt_128bit (struct common_glue_ctx const*,struct blkcipher_desc*,struct blkcipher_walk*) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 int glue_fpu_begin (unsigned int const,int /*<<< orphan*/ ,struct blkcipher_desc*,int,unsigned int) ; 
 int /*<<< orphan*/  glue_fpu_end (int) ; 

int glue_cbc_decrypt_128bit(const struct common_glue_ctx *gctx,
			    struct blkcipher_desc *desc,
			    struct scatterlist *dst,
			    struct scatterlist *src, unsigned int nbytes)
{
	const unsigned int bsize = 128 / 8;
	bool fpu_enabled = false;
	struct blkcipher_walk walk;
	int err;

	blkcipher_walk_init(&walk, dst, src, nbytes);
	err = blkcipher_walk_virt(desc, &walk);

	while ((nbytes = walk.nbytes)) {
		fpu_enabled = glue_fpu_begin(bsize, gctx->fpu_blocks_limit,
					     desc, fpu_enabled, nbytes);
		nbytes = __glue_cbc_decrypt_128bit(gctx, desc, &walk);
		err = blkcipher_walk_done(desc, &walk, nbytes);
	}

	glue_fpu_end(fpu_enabled);
	return err;
}