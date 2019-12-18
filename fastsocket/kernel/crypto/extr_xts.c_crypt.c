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
struct sinfo {struct crypto_tfm* tfm; void (* fn ) (struct crypto_tfm*,u8*,u8 const*) ;int /*<<< orphan*/ * t; } ;
struct priv {int /*<<< orphan*/  tweak; int /*<<< orphan*/  child; } ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct blkcipher_walk {unsigned int nbytes; u8* iv; TYPE_4__ dst; TYPE_2__ src; } ;
struct blkcipher_desc {int dummy; } ;
typedef  int /*<<< orphan*/  be128 ;

/* Variables and functions */
 int XTS_BLOCK_SIZE ; 
 int blkcipher_walk_done (struct blkcipher_desc*,struct blkcipher_walk*,unsigned int) ; 
 int blkcipher_walk_virt (struct blkcipher_desc*,struct blkcipher_walk*) ; 
 struct crypto_tfm* crypto_cipher_tfm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf128mul_x_ble (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xts_round (struct sinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crypt(struct blkcipher_desc *d,
		 struct blkcipher_walk *w, struct priv *ctx,
		 void (*tw)(struct crypto_tfm *, u8 *, const u8 *),
		 void (*fn)(struct crypto_tfm *, u8 *, const u8 *))
{
	int err;
	unsigned int avail;
	const int bs = XTS_BLOCK_SIZE;
	struct sinfo s = {
		.tfm = crypto_cipher_tfm(ctx->child),
		.fn = fn
	};
	u8 *wsrc;
	u8 *wdst;

	err = blkcipher_walk_virt(d, w);
	if (!w->nbytes)
		return err;

	s.t = (be128 *)w->iv;
	avail = w->nbytes;

	wsrc = w->src.virt.addr;
	wdst = w->dst.virt.addr;

	/* calculate first value of T */
	tw(crypto_cipher_tfm(ctx->tweak), w->iv, w->iv);

	goto first;

	for (;;) {
		do {
			gf128mul_x_ble(s.t, s.t);

first:
			xts_round(&s, wdst, wsrc);

			wsrc += bs;
			wdst += bs;
		} while ((avail -= bs) >= bs);

		err = blkcipher_walk_done(d, w, avail);
		if (!w->nbytes)
			break;

		avail = w->nbytes;

		wsrc = w->src.virt.addr;
		wdst = w->dst.virt.addr;
	}

	return err;
}