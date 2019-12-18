#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_13__ {TYPE_4__* vtable; } ;
struct TYPE_14__ {size_t out_len; int /*<<< orphan*/  kso; TYPE_1__ dig; } ;
typedef  TYPE_2__ br_hmac_context ;
struct TYPE_15__ {TYPE_4__* vtable; } ;
typedef  TYPE_3__ br_hash_compat_context ;
struct TYPE_16__ {int /*<<< orphan*/  (* out ) (TYPE_4__**,unsigned char*) ;int /*<<< orphan*/  (* update ) (TYPE_4__**,unsigned char*,size_t) ;int /*<<< orphan*/  (* set_state ) (TYPE_4__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init ) (TYPE_4__**) ;} ;
typedef  TYPE_4__ br_hash_class ;

/* Variables and functions */
 size_t block_size (TYPE_4__ const*) ; 
 size_t br_digest_size (TYPE_4__ const*) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__**,unsigned char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub5 (TYPE_4__**,unsigned char*) ; 

size_t
br_hmac_out(const br_hmac_context *ctx, void *out)
{
	const br_hash_class *dig;
	br_hash_compat_context hc;
	unsigned char tmp[64];
	size_t blen, hlen;

	dig = ctx->dig.vtable;
	dig->out(&ctx->dig.vtable, tmp);
	blen = block_size(dig);
	dig->init(&hc.vtable);
	dig->set_state(&hc.vtable, ctx->kso, (uint64_t)blen);
	hlen = br_digest_size(dig);
	dig->update(&hc.vtable, tmp, hlen);
	dig->out(&hc.vtable, tmp);
	memcpy(out, tmp, ctx->out_len);
	return ctx->out_len;
}