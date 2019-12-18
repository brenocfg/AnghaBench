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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 size_t CCDRBG_MAX_ADDITIONALINPUT_SIZE ; 
 size_t CCDRBG_MAX_REQUEST_SIZE ; 
 scalar_t__ CCDRBG_RESEED_INTERVAL ; 
 int CCDRBG_STATUS_NEED_RESEED ; 
 int CCDRBG_STATUS_OK ; 
 int CCDRBG_STATUS_PARAM_ERROR ; 
 int /*<<< orphan*/  cc_require (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end ; 

__attribute__((used)) static int validate_gen_params(uint64_t reseed_counter,  size_t dataOutLength, size_t additionalLength)

{
    int rc=CCDRBG_STATUS_PARAM_ERROR;

    // Zero byte in one request is a valid use-case (21208820)
    cc_require (dataOutLength <= CCDRBG_MAX_REQUEST_SIZE, end); //Requested too many bytes in one request
    cc_require (additionalLength<=CCDRBG_MAX_ADDITIONALINPUT_SIZE, end); //Additional input too long

    // 1. If (reseed_counter > 2^^48), then Return (“Reseed required”, Null, V, Key, reseed_counter).
     rc = CCDRBG_STATUS_NEED_RESEED;
     cc_require (reseed_counter <= CCDRBG_RESEED_INTERVAL, end); //Reseed required

    rc=CCDRBG_STATUS_OK;

end:
    return rc;
}