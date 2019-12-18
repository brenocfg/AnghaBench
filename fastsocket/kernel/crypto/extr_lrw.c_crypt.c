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
struct sinfo {void (* fn ) (struct crypto_tfm*,u8*,u8 const*) ;int /*<<< orphan*/  t; int /*<<< orphan*/  tfm; } ;
struct TYPE_6__ {int /*<<< orphan*/ * mulinc; int /*<<< orphan*/  table; } ;
struct priv {TYPE_1__ table; int /*<<< orphan*/  child; } ;
struct TYPE_9__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_10__ {TYPE_4__ virt; } ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_2__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; TYPE_5__ dst; TYPE_3__ src; scalar_t__ iv; } ;
struct blkcipher_desc {int dummy; } ;
typedef  int /*<<< orphan*/  be128 ;

/* Variables and functions */
 int LRW_BLOCK_SIZE ; 
 int /*<<< orphan*/  be128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 int /*<<< orphan*/  crypto_cipher_tfm (int /*<<< orphan*/ ) ; 
 size_t get_index128 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gf128mul_64k_bbe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lrw_round (struct sinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crypt(struct blkcipher_desc *d,
		 struct blkcipher_walk *w, struct priv *ctx,
		 void (*fn)(struct crypto_tfm *, u8 *, const u8 *))
{
	int err;
	unsigned int avail;
	const int bs = LRW_BLOCK_SIZE;
	struct sinfo s = {
		.tfm = crypto_cipher_tfm(ctx->child),
		.fn = fn
	};
	be128 *iv;
	u8 *wsrc;
	u8 *wdst;

	err = blkcipher_walk_virt(d, w);
	if (!(avail = w->nbytes))
		return err;

	wsrc = w->src.virt.addr;
	wdst = w->dst.virt.addr;

	/* calculate first value of T */
	iv = (be128 *)w->iv;
	s.t = *iv;

	/* T <- I*Key2 */
	gf128mul_64k_bbe(&s.t, ctx->table.table);

	goto first;

	for (;;) {
		do {
			/* T <- I*Key2, using the optimization
			 * discussed in the specification */
			be128_xor(&s.t, &s.t,
				  &ctx->table.mulinc[get_index128(iv)]);
			inc(iv);

first:
			lrw_round(&s, wdst, wsrc);

			wsrc += bs;
			wdst += bs;
		} while ((avail -= bs) >= bs);

		err = blkcipher_walk_done(d, w, avail);
		if (!(avail = w->nbytes))
			break;

		wsrc = w->src.virt.addr;
		wdst = w->dst.virt.addr;
	}

	return err;
}