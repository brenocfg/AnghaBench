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
typedef  int /*<<< orphan*/  br_block_cbcenc_class ;
typedef  int /*<<< orphan*/  br_block_cbcdec_class ;

/* Variables and functions */
 int /*<<< orphan*/  const br_aes_ct64_cbcdec_vtable ; 
 int /*<<< orphan*/  const br_aes_ct64_cbcenc_vtable ; 
 int /*<<< orphan*/  const br_aes_ct_cbcdec_vtable ; 
 int /*<<< orphan*/  const br_aes_ct_cbcenc_vtable ; 
 int /*<<< orphan*/ * br_aes_pwr8_cbcdec_get_vtable () ; 
 int /*<<< orphan*/ * br_aes_pwr8_cbcenc_get_vtable () ; 
 int /*<<< orphan*/ * br_aes_x86ni_cbcdec_get_vtable () ; 
 int /*<<< orphan*/ * br_aes_x86ni_cbcenc_get_vtable () ; 
 int /*<<< orphan*/  br_ssl_engine_set_aes_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  br_ssl_engine_set_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_sslrec_in_cbc_vtable ; 
 int /*<<< orphan*/  br_sslrec_out_cbc_vtable ; 

void
br_ssl_engine_set_default_aes_cbc(br_ssl_engine_context *cc)
{
#if BR_AES_X86NI || BR_POWER8
	const br_block_cbcenc_class *ienc;
	const br_block_cbcdec_class *idec;
#endif

	br_ssl_engine_set_cbc(cc,
		&br_sslrec_in_cbc_vtable,
		&br_sslrec_out_cbc_vtable);
#if BR_AES_X86NI
	ienc = br_aes_x86ni_cbcenc_get_vtable();
	idec = br_aes_x86ni_cbcdec_get_vtable();
	if (ienc != NULL && idec != NULL) {
		br_ssl_engine_set_aes_cbc(cc, ienc, idec);
		return;
	}
#endif
#if BR_POWER8
	ienc = br_aes_pwr8_cbcenc_get_vtable();
	idec = br_aes_pwr8_cbcdec_get_vtable();
	if (ienc != NULL && idec != NULL) {
		br_ssl_engine_set_aes_cbc(cc, ienc, idec);
		return;
	}
#endif
#if BR_64
	br_ssl_engine_set_aes_cbc(cc,
		&br_aes_ct64_cbcenc_vtable,
		&br_aes_ct64_cbcdec_vtable);
#else
	br_ssl_engine_set_aes_cbc(cc,
		&br_aes_ct_cbcenc_vtable,
		&br_aes_ct_cbcdec_vtable);
#endif
}