#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_10__ {int /*<<< orphan*/  kso; int /*<<< orphan*/  ksi; TYPE_4__* dig_vtable; } ;
typedef  TYPE_2__ br_hmac_key_context ;
struct TYPE_9__ {int /*<<< orphan*/  vtable; } ;
struct TYPE_11__ {size_t out_len; int /*<<< orphan*/  kso; TYPE_1__ dig; } ;
typedef  TYPE_3__ br_hmac_context ;
struct TYPE_12__ {int /*<<< orphan*/  (* set_state ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_4__ br_hash_class ;

/* Variables and functions */
 size_t block_size (TYPE_4__ const*) ; 
 size_t br_digest_size (TYPE_4__ const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
br_hmac_init(br_hmac_context *ctx,
	const br_hmac_key_context *kc, size_t out_len)
{
	const br_hash_class *dig;
	size_t blen, hlen;

	dig = kc->dig_vtable;
	blen = block_size(dig);
	dig->init(&ctx->dig.vtable);
	dig->set_state(&ctx->dig.vtable, kc->ksi, (uint64_t)blen);
	memcpy(ctx->kso, kc->kso, sizeof kc->kso);
	hlen = br_digest_size(dig);
	if (out_len > 0 && out_len < hlen) {
		hlen = out_len;
	}
	ctx->out_len = hlen;
}