#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  in; } ;
struct TYPE_10__ {TYPE_2__ vtable; } ;
struct TYPE_11__ {TYPE_3__ gcm; } ;
struct TYPE_12__ {int incrypt; int /*<<< orphan*/  ighash; TYPE_4__ in; TYPE_1__* igcm_in; } ;
typedef  TYPE_5__ br_ssl_engine_context ;
typedef  int /*<<< orphan*/  br_block_ctr_class ;
struct TYPE_8__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char*,size_t,int /*<<< orphan*/ ,unsigned char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  compute_key_block (TYPE_5__*,int,size_t,unsigned char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char*,size_t,int /*<<< orphan*/ ,unsigned char*) ; 

void
br_ssl_engine_switch_gcm_in(br_ssl_engine_context *cc,
	int is_client, int prf_id,
	const br_block_ctr_class *bc_impl, size_t cipher_key_len)
{
	unsigned char kb[72];
	unsigned char *cipher_key, *iv;

	compute_key_block(cc, prf_id, cipher_key_len + 4, kb);
	if (is_client) {
		cipher_key = &kb[cipher_key_len];
		iv = &kb[(cipher_key_len << 1) + 4];
	} else {
		cipher_key = &kb[0];
		iv = &kb[cipher_key_len << 1];
	}
	cc->igcm_in->init(&cc->in.gcm.vtable.in,
		bc_impl, cipher_key, cipher_key_len, cc->ighash, iv);
	cc->incrypt = 1;
}