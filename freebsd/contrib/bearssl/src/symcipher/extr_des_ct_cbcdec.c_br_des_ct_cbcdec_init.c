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
typedef  void* uint32_t ;
struct TYPE_3__ {void** skey; int /*<<< orphan*/  num_rounds; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ br_des_ct_cbcdec_keys ;

/* Variables and functions */
 int /*<<< orphan*/  br_des_ct_cbcdec_vtable ; 
 int /*<<< orphan*/  br_des_ct_keysched (void**,void const*,size_t) ; 
 int /*<<< orphan*/  br_des_rev_skey (void**) ; 

void
br_des_ct_cbcdec_init(br_des_ct_cbcdec_keys *ctx,
	const void *key, size_t len)
{
	ctx->vtable = &br_des_ct_cbcdec_vtable;
	ctx->num_rounds = br_des_ct_keysched(ctx->skey, key, len);
	if (len == 8) {
		br_des_rev_skey(ctx->skey);
	} else {
		int i;

		for (i = 0; i < 48; i += 2) {
			uint32_t t;

			t = ctx->skey[i];
			ctx->skey[i] = ctx->skey[94 - i];
			ctx->skey[94 - i] = t;
			t = ctx->skey[i + 1];
			ctx->skey[i + 1] = ctx->skey[95 - i];
			ctx->skey[95 - i] = t;
		}
	}
}