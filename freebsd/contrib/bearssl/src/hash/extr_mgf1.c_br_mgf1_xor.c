#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {TYPE_2__ const* vtable; } ;
typedef  TYPE_1__ br_hash_compat_context ;
struct TYPE_10__ {int /*<<< orphan*/  (* out ) (TYPE_2__ const**,unsigned char*) ;int /*<<< orphan*/  (* update ) (TYPE_2__ const**,unsigned char*,int) ;int /*<<< orphan*/  (* init ) (TYPE_2__ const**) ;} ;
typedef  TYPE_2__ br_hash_class ;

/* Variables and functions */
 size_t br_digest_size (TYPE_2__ const*) ; 
 int /*<<< orphan*/  br_enc32be (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const**) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__ const**,void const*,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__ const**,unsigned char*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__ const**,unsigned char*) ; 

void
br_mgf1_xor(void *data, size_t len,
	const br_hash_class *dig, const void *seed, size_t seed_len)
{
	unsigned char *buf;
	size_t u, hlen;
	uint32_t c;

	buf = data;
	hlen = br_digest_size(dig);
	for (u = 0, c = 0; u < len; u += hlen, c ++) {
		br_hash_compat_context hc;
		unsigned char tmp[64];
		size_t v;

		hc.vtable = dig;
		dig->init(&hc.vtable);
		dig->update(&hc.vtable, seed, seed_len);
		br_enc32be(tmp, c);
		dig->update(&hc.vtable, tmp, 4);
		dig->out(&hc.vtable, tmp);
		for (v = 0; v < hlen; v ++) {
			if ((u + v) >= len) {
				break;
			}
			buf[u + v] ^= tmp[v];
		}
	}
}