#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct entropy_store {int input_rotate; unsigned long add_ptr; int* pool; int /*<<< orphan*/  lock; TYPE_1__* poolinfo; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u32 ;
struct TYPE_2__ {int poolwords; unsigned long tap1; unsigned long tap2; unsigned long tap3; unsigned long tap4; unsigned long tap5; } ;

/* Variables and functions */
 int rol32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mix_pool_bytes_extract(struct entropy_store *r, const void *in,
				   int nbytes, __u8 out[64])
{
	static __u32 const twist_table[8] = {
		0x00000000, 0x3b6e20c8, 0x76dc4190, 0x4db26158,
		0xedb88320, 0xd6d6a3e8, 0x9b64c2b0, 0xa00ae278 };
	unsigned long i, j, tap1, tap2, tap3, tap4, tap5;
	int input_rotate;
	int wordmask = r->poolinfo->poolwords - 1;
	const char *bytes = in;
	__u32 w;
	unsigned long flags;

	/* Taps are constant, so we can load them without holding r->lock.  */
	tap1 = r->poolinfo->tap1;
	tap2 = r->poolinfo->tap2;
	tap3 = r->poolinfo->tap3;
	tap4 = r->poolinfo->tap4;
	tap5 = r->poolinfo->tap5;

	spin_lock_irqsave(&r->lock, flags);
	input_rotate = r->input_rotate;
	i = r->add_ptr;

	/* mix one byte at a time to simplify size handling and churn faster */
	while (nbytes--) {
		w = rol32(*bytes++, input_rotate & 31);
		i = (i - 1) & wordmask;

		/* XOR in the various taps */
		w ^= r->pool[i];
		w ^= r->pool[(i + tap1) & wordmask];
		w ^= r->pool[(i + tap2) & wordmask];
		w ^= r->pool[(i + tap3) & wordmask];
		w ^= r->pool[(i + tap4) & wordmask];
		w ^= r->pool[(i + tap5) & wordmask];

		/* Mix the result back in with a twist */
		r->pool[i] = (w >> 3) ^ twist_table[w & 7];

		/*
		 * Normally, we add 7 bits of rotation to the pool.
		 * At the beginning of the pool, add an extra 7 bits
		 * rotation, so that successive passes spread the
		 * input bits across the pool evenly.
		 */
		input_rotate += i ? 7 : 14;
	}

	r->input_rotate = input_rotate;
	r->add_ptr = i;

	if (out)
		for (j = 0; j < 16; j++)
			((__u32 *)out)[j] = r->pool[(i - j) & wordmask];

	spin_unlock_irqrestore(&r->lock, flags);
}