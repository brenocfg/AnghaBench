#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  vtable; } ;
typedef  TYPE_1__ gen_hash_context ;
struct TYPE_6__ {int count; int /*<<< orphan*/  buf; TYPE_3__** impl; } ;
typedef  TYPE_2__ br_multihash_context ;
struct TYPE_7__ {size_t desc; int /*<<< orphan*/  (* out ) (int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* set_state ) (int /*<<< orphan*/ *,unsigned char const*,int) ;} ;
typedef  TYPE_3__ br_hash_class ;

/* Variables and functions */
 size_t BR_HASHDESC_OUT_MASK ; 
 size_t BR_HASHDESC_OUT_OFF ; 
 int get_state_offset (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,void*) ; 

size_t
br_multihash_out(const br_multihash_context *ctx, int id, void *dst)
{
	const br_hash_class *hc;
	gen_hash_context g;
	const unsigned char *state;

	hc = ctx->impl[id - 1];
	if (hc == NULL) {
		return 0;
	}
	state = (const unsigned char *)ctx + get_state_offset(id);
	hc->set_state(&g.vtable, state, ctx->count & ~(uint64_t)127);
	hc->update(&g.vtable, ctx->buf, ctx->count & (uint64_t)127);
	hc->out(&g.vtable, dst);
	return (hc->desc >> BR_HASHDESC_OUT_OFF) & BR_HASHDESC_OUT_MASK;
}