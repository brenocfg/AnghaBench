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
struct TYPE_4__ {int /*<<< orphan*/  local_bda; scalar_t__ rrand; int /*<<< orphan*/  rand_enc_proc_state; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_GEN_COMPARE ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_calculate_comfirm (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_debug_print_nbyte_little_endian (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

void smp_generate_compare (tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    UNUSED(p_data);

    SMP_TRACE_DEBUG ("smp_generate_compare \n");
    p_cb->rand_enc_proc_state = SMP_GEN_COMPARE;
    smp_debug_print_nbyte_little_endian ((UINT8 *)p_cb->rrand,  (const UINT8 *)"peer rand", 16);
    smp_calculate_comfirm(p_cb, p_cb->rrand, p_cb->local_bda);
}