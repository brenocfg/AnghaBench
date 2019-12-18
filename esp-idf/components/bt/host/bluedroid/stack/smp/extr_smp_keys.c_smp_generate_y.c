#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSMP_STATUS ;
typedef  int /*<<< orphan*/  tSMP_INT_DATA ;
typedef  int /*<<< orphan*/  tSMP_ENC ;
struct TYPE_5__ {int /*<<< orphan*/  enc_rand; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  int /*<<< orphan*/  BT_OCTET16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_GetDeviceDHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_OCTET16_LEN ; 
 int /*<<< orphan*/  BT_OCTET8_LEN ; 
 int /*<<< orphan*/  SMP_AUTH_CMPL_EVT ; 
 int /*<<< orphan*/  SMP_Encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMP_PAIR_FAIL_UNKNOWN ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  SMP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_process_ediv (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_sm_event (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smp_generate_y(tSMP_CB *p_cb, tSMP_INT_DATA *p)
{
    UNUSED(p);

    BT_OCTET16  dhk;
    tSMP_ENC   output;
    tSMP_STATUS     status = SMP_PAIR_FAIL_UNKNOWN;


    SMP_TRACE_DEBUG ("smp_generate_y \n");
    BTM_GetDeviceDHK(dhk);

    if (!SMP_Encrypt(dhk, BT_OCTET16_LEN, p_cb->enc_rand,
                     BT_OCTET8_LEN, &output)) {
        SMP_TRACE_ERROR("smp_generate_y failed");
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &status);
    } else {
        smp_process_ediv(p_cb, &output);
    }
}