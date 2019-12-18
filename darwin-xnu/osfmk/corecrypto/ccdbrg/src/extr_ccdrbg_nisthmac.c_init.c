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
struct ccdrbg_nisthmac_state {scalar_t__ vsize; scalar_t__ v; scalar_t__ nextvptr; scalar_t__ vptr; scalar_t__ keysize; TYPE_1__* custom; scalar_t__ bytesLeft; } ;
struct ccdrbg_info {TYPE_1__* custom; } ;
struct ccdigest_info {scalar_t__ output_size; } ;
struct TYPE_2__ {struct ccdigest_info* di; } ;

/* Variables and functions */
 int CCDRBG_STATUS_OK ; 
 int /*<<< orphan*/  done (struct ccdrbg_state*) ; 
 int /*<<< orphan*/  dumpState (char*,struct ccdrbg_nisthmac_state*) ; 
 int /*<<< orphan*/  hmac_dbrg_instantiate_algorithm (struct ccdrbg_state*,size_t,void const*,size_t,void const*,size_t,void const*) ; 
 int validate_inputs (struct ccdrbg_nisthmac_state*,size_t,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int init(const struct ccdrbg_info *info, struct ccdrbg_state *drbg,
                size_t entropyLength, const void* entropy,
                size_t nonceLength, const void* nonce,
                size_t psLength, const void* ps)
{
    struct ccdrbg_nisthmac_state *state=(struct ccdrbg_nisthmac_state *)drbg;
    state->bytesLeft = 0;
    state->custom = info->custom; //we only need to get the custom parameter from the info structure.

    int rc = validate_inputs(state , entropyLength, 0, psLength);
    if(rc!=CCDRBG_STATUS_OK){
        //clear everything if cannot initialize. The idea is that if the caller doesn't check the output of init() and init() fails,
        //the system crashes by NULL dereferencing after a call to generate, rather than generating bad random numbers.
        done(drbg);
        return rc;
    }

    const struct ccdigest_info *di = state->custom->di;
    state->vsize = di->output_size;
    state->keysize = di->output_size;
    state->vptr=state->v;
    state->nextvptr=state->v+state->vsize;

    // 7. (V, Key, reseed_counter) = HMAC_DRBG_Instantiate_algorithm (entropy_input, personalization_string).
    hmac_dbrg_instantiate_algorithm(drbg, entropyLength, entropy, nonceLength, nonce, psLength, ps);

#if DRBG_NISTHMAC_DEBUG
    dumpState("Init: ", state);
#endif
    return CCDRBG_STATUS_OK;

}