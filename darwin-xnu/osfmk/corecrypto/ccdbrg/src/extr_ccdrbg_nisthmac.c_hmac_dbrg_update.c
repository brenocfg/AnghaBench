#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ccdrbg_state {int dummy; } ;
struct ccdrbg_nisthmac_state {size_t vsize; void const* vptr; void const* nextvptr; int /*<<< orphan*/  key; int /*<<< orphan*/  keysize; scalar_t__ bytesLeft; TYPE_1__* custom; } ;
struct ccdigest_info {int /*<<< orphan*/  block_size; int /*<<< orphan*/  state_size; } ;
struct TYPE_2__ {struct ccdigest_info* di; } ;

/* Variables and functions */
 int CCDRBG_STATUS_ABORT ; 
 int CCDRBG_STATUS_ERROR ; 
 int CCDRBG_STATUS_OK ; 
 scalar_t__ cc_cmp_safe (size_t,void const*,void const*) ; 
 int /*<<< orphan*/  cc_try_abort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cchmac (struct ccdigest_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,void const*,void const*) ; 
 int /*<<< orphan*/  cchmac_ctx_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cchmac_final (struct ccdigest_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cchmac_init (struct ccdigest_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cchmac_update (struct ccdigest_info const*,int /*<<< orphan*/ ,size_t,void const*) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  done (struct ccdrbg_state*) ; 

__attribute__((used)) static int hmac_dbrg_update(struct ccdrbg_state *drbg,
                            size_t daLen, const void *da,
                            size_t dbLen, const void *db,
                            size_t dcLen, const void *dc
                            )
{
    int rc=CCDRBG_STATUS_ERROR;
    struct ccdrbg_nisthmac_state *state = (struct ccdrbg_nisthmac_state *)drbg;
    const struct ccdigest_info *di = state->custom->di;

    const unsigned char cZero = 0x00;
    const unsigned char cOne  = 0x01;

    cchmac_ctx_decl(di->state_size, di->block_size, ctx);
    cchmac_init(di, ctx, state->keysize, state->key);

    // 1. K = HMAC (K, V || 0x00 || provided_data).
    cchmac_update(di, ctx, state->vsize, state->vptr);
    cchmac_update(di, ctx, 1, &cZero);
    if (da && daLen) cchmac_update(di, ctx, daLen, da);
    if (db && dbLen) cchmac_update(di, ctx, dbLen, db);
    if (dc && dcLen) cchmac_update(di, ctx, dcLen, dc);
    cchmac_final(di, ctx, state->key);

    // One parameter must be non-empty, or return
    if (((da && daLen) || (db && dbLen) || (dc && dcLen))) {
        //  2. V=HMAC(K,V).
        cchmac(di, state->keysize, state->key, state->vsize, state->vptr, state->vptr);
        //  4. K = HMAC (K, V || 0x01 || provided_data).
        cchmac_init(di, ctx, state->keysize, state->key);
        cchmac_update(di, ctx, state->vsize, state->vptr);
        cchmac_update(di, ctx, 1, &cOne);
        if (da && daLen) cchmac_update(di, ctx, daLen, da);
        if (db && dbLen) cchmac_update(di, ctx, dbLen, db);
        if (dc && dcLen) cchmac_update(di, ctx, dcLen, dc);
        cchmac_final(di, ctx, state->key);
    }
    //  If additional data 5. V=HMAC(K,V)
    //  If no addtional data, this is step 2. V=HMAC(K,V).
    state->bytesLeft = 0;

    // FIPS 140-2 4.9.2 Conditional Tests
    // "the first n-bit block generated after power-up, initialization, or reset shall not be used, but shall be saved for comparison with the next n-bit block to be generated"
    // Generate the first block and the second block. Compare for FIPS and discard the first block
    // We keep the second block as the first set of data to be returned
    cchmac(di, state->keysize, state->key, state->vsize, state->vptr, state->vptr);     // First block
    cchmac(di, state->keysize, state->key, state->vsize, state->vptr, state->nextvptr); // First to be returned
    if (0==cc_cmp_safe(state->vsize, state->vptr, state->nextvptr)) {
        //The world as we know it has come to an end
        //the DRBG data structure is zeroized. subsequent calls to
        //DRBG ends up in NULL dereferencing and/or unpredictable state.
        //catastrophic error in SP 800-90A
        done(drbg);
        rc=CCDRBG_STATUS_ABORT;
        cc_try_abort(NULL);
        goto errOut;
    }
    rc=CCDRBG_STATUS_OK;
errOut:
    return rc;
}