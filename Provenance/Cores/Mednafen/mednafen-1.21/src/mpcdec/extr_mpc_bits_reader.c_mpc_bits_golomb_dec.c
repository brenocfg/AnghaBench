#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int mpc_uint_t ;
typedef  unsigned int mpc_int32_t ;
struct TYPE_3__ {int* buff; int count; } ;
typedef  TYPE_1__ mpc_bits_reader ;

/* Variables and functions */

mpc_int32_t mpc_bits_golomb_dec(mpc_bits_reader * r, const mpc_uint_t k)
{
	unsigned int l = 0;
	unsigned int code = r->buff[0] & ((1 << r->count) - 1);

	while( code == 0 ) {
		l += r->count;
		r->buff++;
		code = r->buff[0];
		r->count = 8;
	}

	while( ((1 << (r->count - 1)) & code) == 0 ) {
		l++;
		r->count--;
	}
	r->count--;

	while( r->count < k ) {
		r->buff++;
		r->count += 8;
		code = (code << 8) | r->buff[0];
	}

	r->count -= k;

	return (l << k) | ((code >> r->count) & ((1 << k) - 1));
}