#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  p_data; int /*<<< orphan*/  key_type; } ;
typedef  TYPE_1__ tSMP_KEY ;
struct TYPE_9__ {int /*<<< orphan*/  param_buf; } ;
typedef  TYPE_2__ tSMP_ENC ;
struct TYPE_10__ {int /*<<< orphan*/  loc_enc_size; } ;
typedef  TYPE_3__ tSMP_CB ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_KEY_READY_EVT ; 
 int /*<<< orphan*/  SMP_KEY_TYPE_STK ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  SMP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  smp_mask_enc_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_sm_event (TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void smp_process_stk(tSMP_CB *p_cb, tSMP_ENC *p)
{
    tSMP_KEY    key;

    SMP_TRACE_DEBUG ("smp_process_stk ");
#if (SMP_DEBUG == TRUE)
    SMP_TRACE_ERROR("STK Generated");
#endif
    smp_mask_enc_key(p_cb->loc_enc_size, p->param_buf);

    key.key_type = SMP_KEY_TYPE_STK;
    key.p_data   = p->param_buf;

    smp_sm_event(p_cb, SMP_KEY_READY_EVT, &key);
}