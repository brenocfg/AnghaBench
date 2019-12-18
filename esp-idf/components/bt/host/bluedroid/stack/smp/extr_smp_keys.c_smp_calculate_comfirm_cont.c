#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSMP_STATUS ;
struct TYPE_12__ {int /*<<< orphan*/ * param_buf; } ;
typedef  TYPE_1__ tSMP_ENC ;
struct TYPE_13__ {int rand_enc_proc_state; int /*<<< orphan*/  tk; } ;
typedef  TYPE_2__ tSMP_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ BT_OCTET16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_OCTET16_LEN ; 
 int /*<<< orphan*/  SMP_AUTH_CMPL_EVT ; 
 int /*<<< orphan*/  SMP_Encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
#define  SMP_GEN_COMPARE 129 
#define  SMP_GEN_CONFIRM 128 
 int /*<<< orphan*/  SMP_PAIR_FAIL_UNKNOWN ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  SMP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  smp_debug_print_nbyte_little_endian (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  smp_gen_p2_4_confirm (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  smp_process_compare (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  smp_process_confirm (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  smp_sm_event (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_xor_128 (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smp_calculate_comfirm_cont(tSMP_CB *p_cb, tSMP_ENC *p)
{
    BT_OCTET16    p2;
    tSMP_ENC      output;
    tSMP_STATUS     status = SMP_PAIR_FAIL_UNKNOWN;

    SMP_TRACE_DEBUG ("smp_calculate_comfirm_cont \n");
#if SMP_DEBUG == TRUE
    SMP_TRACE_DEBUG("Confirm step 1 p1' = e(k, r XOR p1)  Generated\n");
    smp_debug_print_nbyte_little_endian (p->param_buf, (const UINT8 *)"C1", 16);
#endif

    smp_gen_p2_4_confirm(p_cb, p2);

    /* calculate p2 = (p1' XOR p2) */
    smp_xor_128(p2, p->param_buf);
    smp_debug_print_nbyte_little_endian ((UINT8 *)p2, (const UINT8 *)"p2' = C1 xor p2", 16);

    /* calculate: Confirm = E(k, p1' XOR p2) */
    if (!SMP_Encrypt(p_cb->tk, BT_OCTET16_LEN, p2, BT_OCTET16_LEN, &output)) {
        SMP_TRACE_ERROR("smp_calculate_comfirm_cont failed\n");
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &status);
    } else {
        SMP_TRACE_DEBUG("p_cb->rand_enc_proc_state=%d\n", p_cb->rand_enc_proc_state);
        switch (p_cb->rand_enc_proc_state) {
        case SMP_GEN_CONFIRM:
            smp_process_confirm(p_cb, &output);
            break;

        case SMP_GEN_COMPARE:
            smp_process_compare(p_cb, &output);
            break;
        }
    }
}