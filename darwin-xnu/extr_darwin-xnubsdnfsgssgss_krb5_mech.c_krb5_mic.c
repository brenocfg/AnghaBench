#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_2__* gss_buffer_t ;
typedef  TYPE_3__* crypto_ctx_t ;
struct TYPE_16__ {int output_size; } ;
struct TYPE_13__ {void** ikey; } ;
struct TYPE_15__ {int flags; int /*<<< orphan*/  digest_size; TYPE_8__* di; int /*<<< orphan*/  keylen; void** ckey; TYPE_1__ ks; int /*<<< orphan*/  lock; } ;
struct TYPE_14__ {int /*<<< orphan*/  value; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int CRYPTO_KS_ALLOCED ; 
 int GSS_RCV ; 
 int GSS_SND ; 
 int /*<<< orphan*/  cc_key_schedule_create (TYPE_3__*) ; 
 int /*<<< orphan*/  cchmac_di_decl (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cchmac_final (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cchmac_init (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cchmac_update (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hmac_ctx ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
krb5_mic(crypto_ctx_t ctx, gss_buffer_t header, gss_buffer_t bp,  gss_buffer_t trailer, uint8_t *mic, int *verify, int ikey, int reverse)
{
	uint8_t digest[ctx->di->output_size];
	cchmac_di_decl(ctx->di, hmac_ctx);
	int kdx = (verify == NULL) ? (reverse ? GSS_RCV : GSS_SND) : (reverse ? GSS_SND : GSS_RCV);
	void *key2use;

	if (ikey) {
		if (!(ctx->flags & CRYPTO_KS_ALLOCED)) {
			lck_mtx_lock(ctx->lock);
			if (!(ctx->flags & CRYPTO_KS_ALLOCED)) {
				cc_key_schedule_create(ctx);
			}
			ctx->flags |= CRYPTO_KS_ALLOCED;
			lck_mtx_unlock(ctx->lock);
		}
		key2use = ctx->ks.ikey[kdx];
	} else {
		key2use = ctx->ckey[kdx];
	}

	cchmac_init(ctx->di, hmac_ctx, ctx->keylen, key2use);

	if (header) {
		cchmac_update(ctx->di, hmac_ctx, header->length, header->value);
	}

	cchmac_update(ctx->di, hmac_ctx, bp->length, bp->value);

	if (trailer) {
		cchmac_update(ctx->di, hmac_ctx, trailer->length, trailer->value);
	}

	cchmac_final(ctx->di, hmac_ctx, digest);

	if (verify) {
		 *verify = (memcmp(mic, digest, ctx->digest_size) == 0);
	}
	else
		memcpy(mic, digest, ctx->digest_size);

	return (0);
}