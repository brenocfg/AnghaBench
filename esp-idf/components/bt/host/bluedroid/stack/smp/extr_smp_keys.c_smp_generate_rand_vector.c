#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSMP_INT_DATA ;
struct TYPE_3__ {int /*<<< orphan*/  rand_enc_proc_state; } ;
typedef  TYPE_1__ tSMP_CB ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_GEN_RAND_V ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btsnd_hcic_ble_rand (void*) ; 
 int /*<<< orphan*/  smp_rand_back (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smp_generate_rand_vector (tSMP_CB *p_cb, tSMP_INT_DATA *p)
{
    UNUSED(p);

    /* generate EDIV and rand now */
    /* generate random vector */
    SMP_TRACE_DEBUG ("smp_generate_rand_vector\n");
    p_cb->rand_enc_proc_state = SMP_GEN_RAND_V;
    if (!btsnd_hcic_ble_rand((void *)smp_rand_back)) {
        smp_rand_back(NULL);
    }
}