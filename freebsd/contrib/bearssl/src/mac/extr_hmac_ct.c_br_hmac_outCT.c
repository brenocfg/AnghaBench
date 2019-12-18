#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_16__ {TYPE_3__* vtable; } ;
struct TYPE_15__ {size_t out_len; int /*<<< orphan*/  kso; TYPE_2__ dig; } ;
typedef  TYPE_1__ br_hmac_context ;
typedef  TYPE_2__ br_hash_compat_context ;
struct TYPE_17__ {int desc; int (* state ) (TYPE_3__**,unsigned char*) ;int /*<<< orphan*/  (* out ) (TYPE_3__**,unsigned char*) ;int /*<<< orphan*/  (* update ) (TYPE_3__**,unsigned char*,size_t) ;int /*<<< orphan*/  (* set_state ) (TYPE_3__**,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* init ) (TYPE_3__**) ;} ;
typedef  TYPE_3__ br_hash_class ;

/* Variables and functions */
 int BR_HASHDESC_MD_PADDING_128 ; 
 int BR_HASHDESC_MD_PADDING_BE ; 
 int /*<<< orphan*/  CCOPY (int /*<<< orphan*/ ,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  EQ (int,int) ; 
 int /*<<< orphan*/  LE (int,int) ; 
 int /*<<< orphan*/  LT (int,int) ; 
 void* MUX (int /*<<< orphan*/ ,int,int) ; 
 int block_size (TYPE_3__ const*) ; 
 size_t hash_size (TYPE_3__ const*) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_3__**,unsigned char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__**,void const*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__**,unsigned char*,int) ; 
 int stub4 (TYPE_3__**,unsigned char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__**) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub8 (TYPE_3__**,unsigned char*) ; 

size_t
br_hmac_outCT(const br_hmac_context *ctx,
	const void *data, size_t len, size_t min_len, size_t max_len,
	void *out)
{
	/*
	 * Method implemented here is inspired from the descriptions on:
	 *    https://www.imperialviolet.org/2013/02/04/luckythirteen.html
	 *
	 * Principle: we input bytes one by one. We use a MUX to push
	 * padding bytes instead of data bytes when appropriate. At each
	 * block limit, we get the current hash function state: this is
	 * a potential output, since we handle MD padding ourselves.
	 *
	 * be     1 for big-endian, 0 for little-endian
	 * po     minimal MD padding length
	 * bs     block size (always a power of 2)
	 * hlen   hash output size
	 */

	const br_hash_class *dig;
	br_hash_compat_context hc;
	int be;
	uint32_t po, bs;
	uint32_t kr, km, kl, kz, u;
	uint64_t count, ncount, bit_len;
	unsigned char tmp1[64], tmp2[64];
	size_t hlen;

	/*
	 * Copy the current hash context.
	 */
	hc = ctx->dig;

	/*
	 * Get function-specific information.
	 */
	dig = hc.vtable;
	be = (dig->desc & BR_HASHDESC_MD_PADDING_BE) != 0;
	po = 9;
	if (dig->desc & BR_HASHDESC_MD_PADDING_128) {
		po += 8;
	}
	bs = block_size(dig);
	hlen = hash_size(dig);

	/*
	 * Get current input length and compute total bit length.
	 */
	count = dig->state(&hc.vtable, tmp1);
	bit_len = (count + (uint64_t)len) << 3;

	/*
	 * We can input the blocks that we are sure we will use.
	 * This offers better performance (no MUX for these blocks)
	 * and also ensures that the remaining lengths fit on 32 bits.
	 */
	ncount = (count + (uint64_t)min_len) & ~(uint64_t)(bs - 1);
	if (ncount > count) {
		size_t zlen;

		zlen = (size_t)(ncount - count);
		dig->update(&hc.vtable, data, zlen);
		data = (const unsigned char *)data + zlen;
		len -= zlen;
		max_len -= zlen;
		count = ncount;
	}

	/*
	 * At that point:
	 * -- 'count' contains the number of bytes already processed
	 * (in total).
	 * -- We must input 'len' bytes. 'min_len' is unimportant: we
	 * used it to know how many full blocks we could process
	 * directly. Now only len and max_len matter.
	 *
	 * We compute kr, kl, kz and km.
	 *  kr   number of input bytes already in the current block
	 *  km   index of the first byte after the end of the last padding
	 *       block, if length is max_len
	 *  kz   index of the last byte of the actual last padding block
	 *  kl   index of the start of the encoded length
	 *
	 * km, kz and kl are counted from the current offset in the
	 * input data.
	 */
	kr = (uint32_t)count & (bs - 1);
	kz = ((kr + (uint32_t)len + po + bs - 1) & ~(bs - 1)) - 1 - kr;
	kl = kz - 7;
	km = ((kr + (uint32_t)max_len + po + bs - 1) & ~(bs - 1)) - kr;

	/*
	 * We must now process km bytes. For index u from 0 to km-1:
	 *   d is from data[] if u < max_len, 0x00 otherwise
	 *   e is an encoded length byte or 0x00, depending on u
	 * The tests for d and e need not be constant-time, since
	 * they relate only to u and max_len, not to the actual length.
	 *
	 * Actual input length is then:
	 *   d      if u < len
	 *   0x80   if u == len
	 *   0x00   if u > len and u < kl
	 *   e      if u >= kl
	 *
	 * Hash state is obtained whenever we reach a full block. This
	 * is the result we want if and only if u == kz.
	 */
	memset(tmp2, 0, sizeof tmp2);
	for (u = 0; u < km; u ++) {
		uint32_t v;
		uint32_t d, e, x0, x1;
		unsigned char x[1];

		d = (u < max_len) ? ((const unsigned char *)data)[u] : 0x00;
		v = (kr + u) & (bs - 1);
		if (v >= (bs - 8)) {
			unsigned j;

			j = (v - (bs - 8)) << 3;
			if (be) {
				e = (uint32_t)(bit_len >> (56 - j));
			} else {
				e = (uint32_t)(bit_len >> j);
			}
			e &= 0xFF;
		} else {
			e = 0x00;
		}
		x0 = MUX(EQ(u, (uint32_t)len), 0x80, d);
		x1 = MUX(LT(u, kl), 0x00, e);
		x[0] = MUX(LE(u, (uint32_t)len), x0, x1);
		dig->update(&hc.vtable, x, 1);
		if (v == (bs - 1)) {
			dig->state(&hc.vtable, tmp1);
			CCOPY(EQ(u, kz), tmp2, tmp1, hlen);
		}
	}

	/*
	 * Inner hash output is in tmp2[]; we finish processing.
	 */
	dig->init(&hc.vtable);
	dig->set_state(&hc.vtable, ctx->kso, (uint64_t)bs);
	dig->update(&hc.vtable, tmp2, hlen);
	dig->out(&hc.vtable, tmp2);
	memcpy(out, tmp2, ctx->out_len);
	return ctx->out_len;
}