#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  vtable; } ;
struct TYPE_18__ {TYPE_3__ cbc; } ;
struct TYPE_15__ {scalar_t__ version; } ;
struct TYPE_19__ {int incrypt; TYPE_4__ in; TYPE_2__* icbc_in; TYPE_1__ session; } ;
typedef  TYPE_5__ br_ssl_engine_context ;
struct TYPE_20__ {size_t desc; } ;
typedef  TYPE_6__ br_hash_class ;
struct TYPE_21__ {size_t block_size; } ;
typedef  TYPE_7__ br_block_cbcdec_class ;
struct TYPE_16__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *,TYPE_7__ const*,unsigned char*,size_t,TYPE_6__ const*,unsigned char*,size_t,size_t,unsigned char*) ;} ;

/* Variables and functions */
 size_t BR_HASHDESC_OUT_MASK ; 
 size_t BR_HASHDESC_OUT_OFF ; 
 scalar_t__ BR_TLS11 ; 
 TYPE_6__* br_ssl_engine_get_hash (TYPE_5__*,int) ; 
 int /*<<< orphan*/  compute_key_block (TYPE_5__*,int,size_t,unsigned char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_7__ const*,unsigned char*,size_t,TYPE_6__ const*,unsigned char*,size_t,size_t,unsigned char*) ; 

void
br_ssl_engine_switch_cbc_in(br_ssl_engine_context *cc,
	int is_client, int prf_id, int mac_id,
	const br_block_cbcdec_class *bc_impl, size_t cipher_key_len)
{
	unsigned char kb[192];
	unsigned char *cipher_key, *mac_key, *iv;
	const br_hash_class *imh;
	size_t mac_key_len, mac_out_len, iv_len;

	imh = br_ssl_engine_get_hash(cc, mac_id);
	mac_out_len = (imh->desc >> BR_HASHDESC_OUT_OFF) & BR_HASHDESC_OUT_MASK;
	mac_key_len = mac_out_len;

	/*
	 * TLS 1.1+ uses per-record explicit IV, so no IV to generate here.
	 */
	if (cc->session.version >= BR_TLS11) {
		iv_len = 0;
	} else {
		iv_len = bc_impl->block_size;
	}
	compute_key_block(cc, prf_id,
		mac_key_len + cipher_key_len + iv_len, kb);
	if (is_client) {
		mac_key = &kb[mac_key_len];
		cipher_key = &kb[(mac_key_len << 1) + cipher_key_len];
		iv = &kb[((mac_key_len + cipher_key_len) << 1) + iv_len];
	} else {
		mac_key = &kb[0];
		cipher_key = &kb[mac_key_len << 1];
		iv = &kb[(mac_key_len + cipher_key_len) << 1];
	}
	if (iv_len == 0) {
		iv = NULL;
	}
	cc->icbc_in->init(&cc->in.cbc.vtable,
		bc_impl, cipher_key, cipher_key_len,
		imh, mac_key, mac_key_len, mac_out_len, iv);
	cc->incrypt = 1;
}