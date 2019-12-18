#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSMP_INT_DATA ;
struct TYPE_4__ {int /*<<< orphan*/  rand_enc_proc_state; int /*<<< orphan*/  div; int /*<<< orphan*/  pairing_bda; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_GEN_DIV_CSRK ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ btm_get_local_div (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btsnd_hcic_ble_rand (void*) ; 
 int /*<<< orphan*/  smp_compute_csrk (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rand_back (int /*<<< orphan*/ *) ; 

void smp_generate_csrk(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UNUSED(p_data);

    BOOLEAN     div_status;

    SMP_TRACE_DEBUG ("smp_generate_csrk");

    div_status = btm_get_local_div(p_cb->pairing_bda, &p_cb->div);
    if (div_status) {
        smp_compute_csrk(p_cb, NULL);
    } else {
        SMP_TRACE_DEBUG ("Generate DIV for CSRK");
        p_cb->rand_enc_proc_state = SMP_GEN_DIV_CSRK;
        if (!btsnd_hcic_ble_rand((void *)smp_rand_back)) {
            smp_rand_back(NULL);
        }
    }
}