#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  br_ssl_engine_context ;
typedef  scalar_t__ br_ghash ;
typedef  int /*<<< orphan*/  br_block_ctr_class ;

/* Variables and functions */
 int /*<<< orphan*/  const br_aes_ct64_ctr_vtable ; 
 int /*<<< orphan*/  const br_aes_ct_ctr_vtable ; 
 int /*<<< orphan*/ * br_aes_pwr8_ctr_get_vtable () ; 
 int /*<<< orphan*/ * br_aes_x86ni_ctr_get_vtable () ; 
 int /*<<< orphan*/  br_ghash_ctmul ; 
 int /*<<< orphan*/  br_ghash_ctmul32 ; 
 int /*<<< orphan*/  br_ghash_ctmul64 ; 
 scalar_t__ br_ghash_pclmul_get () ; 
 scalar_t__ br_ghash_pwr8_get () ; 
 int /*<<< orphan*/  br_ssl_engine_set_aes_ctr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  br_ssl_engine_set_gcm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_ghash (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  br_sslrec_in_gcm_vtable ; 
 int /*<<< orphan*/  br_sslrec_out_gcm_vtable ; 

void
br_ssl_engine_set_default_aes_gcm(br_ssl_engine_context *cc)
{
#if BR_AES_X86NI || BR_POWER8
	const br_block_ctr_class *ictr;
	br_ghash ighash;
#endif

	br_ssl_engine_set_gcm(cc,
		&br_sslrec_in_gcm_vtable,
		&br_sslrec_out_gcm_vtable);
#if BR_AES_X86NI
	ictr = br_aes_x86ni_ctr_get_vtable();
	if (ictr != NULL) {
		br_ssl_engine_set_aes_ctr(cc, ictr);
	} else {
#if BR_64
		br_ssl_engine_set_aes_ctr(cc, &br_aes_ct64_ctr_vtable);
#else
		br_ssl_engine_set_aes_ctr(cc, &br_aes_ct_ctr_vtable);
#endif
	}
#elif BR_POWER8
	ictr = br_aes_pwr8_ctr_get_vtable();
	if (ictr != NULL) {
		br_ssl_engine_set_aes_ctr(cc, ictr);
	} else {
#if BR_64
		br_ssl_engine_set_aes_ctr(cc, &br_aes_ct64_ctr_vtable);
#else
		br_ssl_engine_set_aes_ctr(cc, &br_aes_ct_ctr_vtable);
#endif
	}
#else
#if BR_64
	br_ssl_engine_set_aes_ctr(cc, &br_aes_ct64_ctr_vtable);
#else
	br_ssl_engine_set_aes_ctr(cc, &br_aes_ct_ctr_vtable);
#endif
#endif
#if BR_AES_X86NI
	ighash = br_ghash_pclmul_get();
	if (ighash != 0) {
		br_ssl_engine_set_ghash(cc, ighash);
		return;
	}
#endif
#if BR_POWER8
	ighash = br_ghash_pwr8_get();
	if (ighash != 0) {
		br_ssl_engine_set_ghash(cc, ighash);
		return;
	}
#endif
#if BR_LOMUL
	br_ssl_engine_set_ghash(cc, &br_ghash_ctmul32);
#elif BR_64
	br_ssl_engine_set_ghash(cc, &br_ghash_ctmul64);
#else
	br_ssl_engine_set_ghash(cc, &br_ghash_ctmul);
#endif
}