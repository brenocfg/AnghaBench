#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  vtable; } ;
struct TYPE_7__ {size_t mac_len; int explicit_IV; int /*<<< orphan*/  iv; int /*<<< orphan*/  mac; TYPE_1__ bc; scalar_t__ seq; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_2__ br_sslrec_in_cbc_context ;
typedef  int /*<<< orphan*/  br_hash_class ;
struct TYPE_8__ {int /*<<< orphan*/  block_size; int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *,void const*,size_t) ;} ;
typedef  TYPE_3__ br_block_cbcdec_class ;

/* Variables and functions */
 int /*<<< orphan*/  br_hmac_key_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void const*,size_t) ; 
 int /*<<< orphan*/  br_sslrec_in_cbc_vtable ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static void
in_cbc_init(br_sslrec_in_cbc_context *cc,
	const br_block_cbcdec_class *bc_impl,
	const void *bc_key, size_t bc_key_len,
	const br_hash_class *dig_impl,
	const void *mac_key, size_t mac_key_len, size_t mac_out_len,
	const void *iv)
{
	cc->vtable = &br_sslrec_in_cbc_vtable;
	cc->seq = 0;
	bc_impl->init(&cc->bc.vtable, bc_key, bc_key_len);
	br_hmac_key_init(&cc->mac, dig_impl, mac_key, mac_key_len);
	cc->mac_len = mac_out_len;
	if (iv == NULL) {
		memset(cc->iv, 0, sizeof cc->iv);
		cc->explicit_IV = 1;
	} else {
		memcpy(cc->iv, iv, bc_impl->block_size);
		cc->explicit_IV = 0;
	}
}