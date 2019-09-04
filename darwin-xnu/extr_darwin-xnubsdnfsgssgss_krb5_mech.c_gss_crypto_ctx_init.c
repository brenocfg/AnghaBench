#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_13__ {void** ikey; int /*<<< orphan*/ * dec; int /*<<< orphan*/ * enc; } ;
struct crypto_ctx {int etype; int mpad; int digest_size; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ckey; TYPE_6__* enc_mode; int /*<<< orphan*/  flags; TYPE_6__* di; void* key; TYPE_3__ ks; TYPE_6__* dec_mode; int /*<<< orphan*/  keylen; TYPE_4__* gss_ctx; } ;
typedef  TYPE_4__* lucid_context_t ;
struct TYPE_15__ {int block_size; } ;
struct TYPE_11__ {void* key_val; int /*<<< orphan*/  key_len; } ;
struct TYPE_12__ {int etype; TYPE_1__ key; } ;
struct TYPE_14__ {int /*<<< orphan*/  initiate; TYPE_2__ ctx_key; } ;

/* Variables and functions */
#define  AES128_CTS_HMAC_SHA1_96 130 
#define  AES256_CTS_HMAC_SHA1_96 129 
 int /*<<< orphan*/  CRYPTO_CTS_ENABLE ; 
#define  DES3_CBC_SHA1_KD 128 
 int ENOTSUP ; 
 size_t GSS_RCV ; 
 size_t GSS_SND ; 
 int /*<<< orphan*/  KRB5_USAGE_ACCEPTOR_SIGN ; 
 int /*<<< orphan*/  KRB5_USAGE_INITIATOR_SIGN ; 
 int KRB5_USAGE_LEN ; 
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int /*<<< orphan*/  assert (TYPE_6__*) ; 
 TYPE_6__* ccaes_cbc_decrypt_mode () ; 
 TYPE_6__* ccaes_cbc_encrypt_mode () ; 
 TYPE_6__* ccdes3_cbc_decrypt_mode () ; 
 TYPE_6__* ccdes3_cbc_encrypt_mode () ; 
 void* ccsha1_di () ; 
 int /*<<< orphan*/  gss_krb5_mech_grp ; 
 int /*<<< orphan*/  krb5_3des_key_derivation (struct crypto_ctx*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_key_derivation (struct crypto_ctx*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_make_usage (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
gss_crypto_ctx_init(struct crypto_ctx *ctx, lucid_context_t lucid)
{
	ctx->gss_ctx = lucid;
	void *key;
	uint8_t usage_string[KRB5_USAGE_LEN];

	ctx->keylen = ctx->gss_ctx->ctx_key.key.key_len;
	key = ctx->gss_ctx->ctx_key.key.key_val;
	ctx->etype = ctx->gss_ctx->ctx_key.etype;
	ctx->key = key;

	switch(ctx->etype) {
	case AES128_CTS_HMAC_SHA1_96:
	case AES256_CTS_HMAC_SHA1_96:
		ctx->enc_mode = ccaes_cbc_encrypt_mode();
		assert(ctx->enc_mode);
		ctx->dec_mode = ccaes_cbc_decrypt_mode();
		assert(ctx->dec_mode);
		ctx->ks.enc = NULL;
		ctx->ks.dec = NULL;
		ctx->di = ccsha1_di();
		assert(ctx->di);
		ctx->flags = CRYPTO_CTS_ENABLE;
		ctx->mpad = 1;
		ctx->digest_size = 12; /* 96 bits */
		krb5_make_usage(ctx->gss_ctx->initiate ?
				KRB5_USAGE_INITIATOR_SIGN : KRB5_USAGE_ACCEPTOR_SIGN,
				0x99, usage_string);
		krb5_key_derivation(ctx, usage_string, KRB5_USAGE_LEN, &ctx->ckey[GSS_SND], ctx->keylen);
		krb5_make_usage(ctx->gss_ctx->initiate ?
				KRB5_USAGE_ACCEPTOR_SIGN : KRB5_USAGE_INITIATOR_SIGN,
				0x99, usage_string);
		krb5_key_derivation(ctx, usage_string, KRB5_USAGE_LEN, &ctx->ckey[GSS_RCV], ctx->keylen);
		break;
	case DES3_CBC_SHA1_KD:
		ctx->enc_mode = ccdes3_cbc_encrypt_mode();
		assert(ctx->enc_mode);
		ctx->dec_mode = ccdes3_cbc_decrypt_mode();
		assert(ctx->dec_mode);
		ctx->ks.ikey[GSS_SND]  = ctx->key;
		ctx->ks.ikey[GSS_RCV]  = ctx->key;
		ctx->di = ccsha1_di();
		assert(ctx->di);
		ctx->flags = 0;
		ctx->mpad = ctx->enc_mode->block_size;
		ctx->digest_size = 20; /* 160 bits */
		krb5_make_usage(KRB5_USAGE_ACCEPTOR_SIGN, 0x99, usage_string);
		krb5_3des_key_derivation(ctx, usage_string, KRB5_USAGE_LEN, &ctx->ckey[GSS_SND]);
		krb5_3des_key_derivation(ctx, usage_string, KRB5_USAGE_LEN, &ctx->ckey[GSS_RCV]);
		break;
	default:
		return (ENOTSUP);
	}

	ctx->lock = lck_mtx_alloc_init(gss_krb5_mech_grp, LCK_ATTR_NULL);

	return (0);
}