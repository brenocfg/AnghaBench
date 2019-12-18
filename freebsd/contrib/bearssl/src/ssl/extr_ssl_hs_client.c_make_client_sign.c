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
struct TYPE_5__ {int /*<<< orphan*/  pad; int /*<<< orphan*/  mhash; } ;
struct TYPE_6__ {TYPE_1__ eng; scalar_t__ hash_id; TYPE_3__** client_auth_vtable; } ;
typedef  TYPE_2__ br_ssl_client_context ;
struct TYPE_7__ {size_t (* do_sign ) (TYPE_3__**,scalar_t__,size_t,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ br_md5_ID ; 
 size_t br_multihash_out (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ br_sha1_ID ; 
 size_t stub1 (TYPE_3__**,scalar_t__,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t
make_client_sign(br_ssl_client_context *ctx)
{
	size_t hv_len;

	/*
	 * Compute hash of handshake messages so far. This "cannot" fail
	 * because the list of supported hash functions provided to the
	 * client certificate handler was trimmed to include only the
	 * hash functions that the multi-hasher supports.
	 */
	if (ctx->hash_id) {
		hv_len = br_multihash_out(&ctx->eng.mhash,
			ctx->hash_id, ctx->eng.pad);
	} else {
		br_multihash_out(&ctx->eng.mhash,
			br_md5_ID, ctx->eng.pad);
		br_multihash_out(&ctx->eng.mhash,
			br_sha1_ID, ctx->eng.pad + 16);
		hv_len = 36;
	}
	return (*ctx->client_auth_vtable)->do_sign(
		ctx->client_auth_vtable, ctx->hash_id, hv_len,
		ctx->eng.pad, sizeof ctx->eng.pad);
}