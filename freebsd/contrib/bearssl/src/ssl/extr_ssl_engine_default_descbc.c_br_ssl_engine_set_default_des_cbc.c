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

/* Variables and functions */
 int /*<<< orphan*/  br_des_ct_cbcdec_vtable ; 
 int /*<<< orphan*/  br_des_ct_cbcenc_vtable ; 
 int /*<<< orphan*/  br_ssl_engine_set_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_ssl_engine_set_des_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_sslrec_in_cbc_vtable ; 
 int /*<<< orphan*/  br_sslrec_out_cbc_vtable ; 

void
br_ssl_engine_set_default_des_cbc(br_ssl_engine_context *cc)
{
	br_ssl_engine_set_cbc(cc,
		&br_sslrec_in_cbc_vtable,
		&br_sslrec_out_cbc_vtable);
	br_ssl_engine_set_des_cbc(cc,
		&br_des_ct_cbcenc_vtable,
		&br_des_ct_cbcdec_vtable);
}