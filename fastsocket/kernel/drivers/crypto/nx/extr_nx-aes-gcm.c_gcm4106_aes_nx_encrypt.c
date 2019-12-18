#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* iv; char* nonce; } ;
struct TYPE_6__ {TYPE_2__ gcm; } ;
struct nx_crypto_ctx {TYPE_3__ priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  tfm; } ;
struct aead_request {char* iv; TYPE_1__ base; } ;

/* Variables and functions */
 int NX_GCM4106_NONCE_LEN ; 
 struct nx_crypto_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int gcm_aes_nx_crypt (struct aead_request*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int gcm4106_aes_nx_encrypt(struct aead_request *req)
{
	struct nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(req->base.tfm);
	char *iv = nx_ctx->priv.gcm.iv;
	char *nonce = nx_ctx->priv.gcm.nonce;

	memcpy(iv, nonce, NX_GCM4106_NONCE_LEN);
	memcpy(iv + NX_GCM4106_NONCE_LEN, req->iv, 8);

	return gcm_aes_nx_crypt(req, 1);
}