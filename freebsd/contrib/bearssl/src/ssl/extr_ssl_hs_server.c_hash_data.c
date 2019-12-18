#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mhash; } ;
struct TYPE_8__ {TYPE_1__ eng; } ;
typedef  TYPE_2__ br_ssl_server_context ;
struct TYPE_9__ {int /*<<< orphan*/  vtable; } ;
typedef  TYPE_3__ br_hash_compat_context ;
struct TYPE_10__ {size_t desc; int /*<<< orphan*/  (* out ) (int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,void const*,size_t) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_4__ br_hash_class ;

/* Variables and functions */
 size_t BR_HASHDESC_OUT_MASK ; 
 size_t BR_HASHDESC_OUT_OFF ; 
 int br_md5_ID ; 
 TYPE_4__* br_multihash_getimpl (int /*<<< orphan*/ *,int) ; 
 int br_sha1_ID ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static size_t
hash_data(br_ssl_server_context *ctx,
	void *dst, int hash_id, const void *src, size_t len)
{
	const br_hash_class *hf;
	br_hash_compat_context hc;

	if (hash_id == 0) {
		unsigned char tmp[36];

		hf = br_multihash_getimpl(&ctx->eng.mhash, br_md5_ID);
		if (hf == NULL) {
			return 0;
		}
		hf->init(&hc.vtable);
		hf->update(&hc.vtable, src, len);
		hf->out(&hc.vtable, tmp);
		hf = br_multihash_getimpl(&ctx->eng.mhash, br_sha1_ID);
		if (hf == NULL) {
			return 0;
		}
		hf->init(&hc.vtable);
		hf->update(&hc.vtable, src, len);
		hf->out(&hc.vtable, tmp + 16);
		memcpy(dst, tmp, 36);
		return 36;
	} else {
		hf = br_multihash_getimpl(&ctx->eng.mhash, hash_id);
		if (hf == NULL) {
			return 0;
		}
		hf->init(&hc.vtable);
		hf->update(&hc.vtable, src, len);
		hf->out(&hc.vtable, dst);
		return (hf->desc >> BR_HASHDESC_OUT_OFF) & BR_HASHDESC_OUT_MASK;
	}
}