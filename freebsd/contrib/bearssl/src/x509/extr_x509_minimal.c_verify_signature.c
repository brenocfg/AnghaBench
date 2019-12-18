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
struct TYPE_6__ {int /*<<< orphan*/  ec; int /*<<< orphan*/  rsa; } ;
struct TYPE_7__ {int key_type; TYPE_1__ key; } ;
typedef  TYPE_2__ br_x509_pkey ;
struct TYPE_8__ {int cert_signer_key_type; size_t cert_sig_hash_oid; int /*<<< orphan*/  cert_sig_len; int /*<<< orphan*/  cert_sig; int /*<<< orphan*/  cert_sig_hash_len; int /*<<< orphan*/  tbs_hash; int /*<<< orphan*/  iec; int /*<<< orphan*/  (* iecdsa ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* irsa ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*) ;} ;
typedef  TYPE_3__ br_x509_minimal_context ;

/* Variables and functions */
 int BR_ERR_X509_BAD_SIGNATURE ; 
 int BR_ERR_X509_UNSUPPORTED ; 
 int BR_ERR_X509_WRONG_KEY_TYPE ; 
#define  BR_KEYTYPE_EC 129 
#define  BR_KEYTYPE_RSA 128 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * t0_datablock ; 

__attribute__((used)) static int
verify_signature(br_x509_minimal_context *ctx, const br_x509_pkey *pk)
{
	int kt;

	kt = ctx->cert_signer_key_type;
	if ((pk->key_type & 0x0F) != kt) {
		return BR_ERR_X509_WRONG_KEY_TYPE;
	}
	switch (kt) {
		unsigned char tmp[64];

	case BR_KEYTYPE_RSA:
		if (ctx->irsa == 0) {
			return BR_ERR_X509_UNSUPPORTED;
		}
		if (!ctx->irsa(ctx->cert_sig, ctx->cert_sig_len,
			&t0_datablock[ctx->cert_sig_hash_oid],
			ctx->cert_sig_hash_len, &pk->key.rsa, tmp))
		{
			return BR_ERR_X509_BAD_SIGNATURE;
		}
		if (memcmp(ctx->tbs_hash, tmp, ctx->cert_sig_hash_len) != 0) {
			return BR_ERR_X509_BAD_SIGNATURE;
		}
		return 0;

	case BR_KEYTYPE_EC:
		if (ctx->iecdsa == 0) {
			return BR_ERR_X509_UNSUPPORTED;
		}
		if (!ctx->iecdsa(ctx->iec, ctx->tbs_hash,
			ctx->cert_sig_hash_len, &pk->key.ec,
			ctx->cert_sig, ctx->cert_sig_len))
		{
			return BR_ERR_X509_BAD_SIGNATURE;
		}
		return 0;

	default:
		return BR_ERR_X509_UNSUPPORTED;
	}
}