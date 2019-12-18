#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSMP_STATUS ;
typedef  int /*<<< orphan*/  tSMP_INT_DATA ;
struct TYPE_8__ {int /*<<< orphan*/  param_buf; } ;
typedef  TYPE_1__ tSMP_ENC ;
struct TYPE_9__ {int div; scalar_t__ csrk; scalar_t__ smp_over_br; } ;
typedef  TYPE_2__ tSMP_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  BT_OCTET16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_GetDeviceEncRoot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_OCTET16_LEN ; 
 int /*<<< orphan*/  SMP_AUTH_CMPL_EVT ; 
 int /*<<< orphan*/  SMP_BR_AUTH_CMPL_EVT ; 
 int /*<<< orphan*/  SMP_Encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  SMP_PAIR_FAIL_UNKNOWN ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*,int) ; 
 int /*<<< orphan*/  SMP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_br_state_machine_event (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_send_csrk_info (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_sm_event (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void smp_compute_csrk(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UNUSED(p_data);

    BT_OCTET16  er;
    UINT8       buffer[4]; /* for (r || DIV)  r=1*/
    UINT16      r = 1;
    UINT8       *p = buffer;
    tSMP_ENC    output;
    tSMP_STATUS   status = SMP_PAIR_FAIL_UNKNOWN;

    SMP_TRACE_DEBUG ("smp_compute_csrk div=%x\n", p_cb->div);
    BTM_GetDeviceEncRoot(er);
    /* CSRK = d1(ER, DIV, 1) */
    UINT16_TO_STREAM(p, p_cb->div);
    UINT16_TO_STREAM(p, r);

    if (!SMP_Encrypt(er, BT_OCTET16_LEN, buffer, 4, &output)) {
        SMP_TRACE_ERROR("smp_generate_csrk failed\n");
        if (p_cb->smp_over_br) {
#if (CLASSIC_BT_INCLUDED == TRUE)
            smp_br_state_machine_event(p_cb, SMP_BR_AUTH_CMPL_EVT, &status);
#endif  ///CLASSIC_BT_INCLUDED == TRUE
        } else {
            smp_sm_event(p_cb, SMP_AUTH_CMPL_EVT, &status);
        }
    } else {
        memcpy((void *)p_cb->csrk, output.param_buf, BT_OCTET16_LEN);
        smp_send_csrk_info(p_cb, NULL);
    }
}