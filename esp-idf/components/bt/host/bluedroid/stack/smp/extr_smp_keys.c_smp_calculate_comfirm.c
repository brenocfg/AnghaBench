#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSMP_STATUS ;
typedef  int /*<<< orphan*/  tSMP_ENC ;
struct TYPE_6__ {int /*<<< orphan*/  tk; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ BT_OCTET16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_OCTET16_LEN ; 
 int /*<<< orphan*/  SMP_AUTH_CMPL_EVT ; 
 int /*<<< orphan*/  SMP_Encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMP_PAIR_FAIL_UNKNOWN ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  SMP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_calculate_comfirm_cont (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_debug_print_nbyte_little_endian (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  smp_gen_p1_4_confirm (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  smp_sm_event (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_xor_128 (scalar_t__,scalar_t__) ; 

void smp_calculate_comfirm (tSMP_CB *p_cb, BT_OCTET16 rand, BD_ADDR bda)
{
    UNUSED(bda);

    BT_OCTET16      p1;
    tSMP_ENC       output;
    tSMP_STATUS     status = SMP_PAIR_FAIL_UNKNOWN;

    SMP_TRACE_DEBUG ("smp_calculate_comfirm \n");
    /* generate p1 = pres || preq || rat' || iat' */
    smp_gen_p1_4_confirm(p_cb, p1);

    /* p1 = rand XOR p1 */
    smp_xor_128(p1, rand);

    smp_debug_print_nbyte_little_endian ((UINT8 *)p1, (const UINT8 *)"P1' = r XOR p1", 16);

    /* calculate e(k, r XOR p1), where k = TK */
    if (!SMP_Encrypt(p_cb->tk, BT_OCTET16_LEN, p1, BT_OCTET16_LEN, &output)) {
        SMP_TRACE_ERROR("smp_generate_csrk failed");
        smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &status);
    } else {
        smp_calculate_comfirm_cont(p_cb, &output);
    }
}