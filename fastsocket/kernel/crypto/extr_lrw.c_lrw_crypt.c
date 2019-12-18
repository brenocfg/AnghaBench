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
struct scatterlist {int dummy; } ;
struct lrw_table_ctx {int /*<<< orphan*/ * mulinc; int /*<<< orphan*/  table; } ;
struct lrw_crypt_req {unsigned int const tbuflen; int /*<<< orphan*/  crypt_ctx; int /*<<< orphan*/  (* crypt_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ;int /*<<< orphan*/ * tbuf; struct lrw_table_ctx* table_ctx; } ;
struct TYPE_7__ {scalar_t__ addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; TYPE_4__ dst; TYPE_2__ src; scalar_t__ iv; } ;
struct blkcipher_desc {int dummy; } ;
typedef  int /*<<< orphan*/  be128 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int LRW_BLOCK_SIZE ; 
 int /*<<< orphan*/  be128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int /*<<< orphan*/  blkcipher_walk_init (struct blkcipher_walk*,struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 size_t get_index128 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gf128mul_64k_bbe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc (int /*<<< orphan*/ *) ; 
 unsigned int min (unsigned int const,unsigned int const) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

int lrw_crypt(struct blkcipher_desc *desc, struct scatterlist *sdst,
	      struct scatterlist *ssrc, unsigned int nbytes,
	      struct lrw_crypt_req *req)
{
	const unsigned int bsize = LRW_BLOCK_SIZE;
	const unsigned int max_blks = req->tbuflen / bsize;
	struct lrw_table_ctx *ctx = req->table_ctx;
	struct blkcipher_walk walk;
	unsigned int nblocks;
	be128 *iv, *src, *dst, *t;
	be128 *t_buf = req->tbuf;
	int err, i;

	BUG_ON(max_blks < 1);

	blkcipher_walk_init(&walk, sdst, ssrc, nbytes);

	err = blkcipher_walk_virt(desc, &walk);
	nbytes = walk.nbytes;
	if (!nbytes)
		return err;

	nblocks = min(walk.nbytes / bsize, max_blks);
	src = (be128 *)walk.src.virt.addr;
	dst = (be128 *)walk.dst.virt.addr;

	/* calculate first value of T */
	iv = (be128 *)walk.iv;
	t_buf[0] = *iv;

	/* T <- I*Key2 */
	gf128mul_64k_bbe(&t_buf[0], ctx->table);

	i = 0;
	goto first;

	for (;;) {
		do {
			for (i = 0; i < nblocks; i++) {
				/* T <- I*Key2, using the optimization
				 * discussed in the specification */
				be128_xor(&t_buf[i], t,
						&ctx->mulinc[get_index128(iv)]);
				inc(iv);
first:
				t = &t_buf[i];

				/* PP <- T xor P */
				be128_xor(dst + i, t, src + i);
			}

			/* CC <- E(Key2,PP) */
			req->crypt_fn(req->crypt_ctx, (u8 *)dst,
				      nblocks * bsize);

			/* C <- T xor CC */
			for (i = 0; i < nblocks; i++)
				be128_xor(dst + i, dst + i, &t_buf[i]);

			src += nblocks;
			dst += nblocks;
			nbytes -= nblocks * bsize;
			nblocks = min(nbytes / bsize, max_blks);
		} while (nblocks > 0);

		err = blkcipher_walk_done(desc, &walk, nbytes);
		nbytes = walk.nbytes;
		if (!nbytes)
			break;

		nblocks = min(nbytes / bsize, max_blks);
		src = (be128 *)walk.src.virt.addr;
		dst = (be128 *)walk.dst.virt.addr;
	}

	return err;
}