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
struct TYPE_4__ {scalar_t__ total_tx_unacked; } ;
typedef  TYPE_1__ tSMP_CB ;

/* Variables and functions */
 int /*<<< orphan*/  smp_proc_pairing_cmpl (TYPE_1__*) ; 

void smp_pairing_cmpl(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    if (p_cb->total_tx_unacked == 0) {
        /* process the pairing complete */
        smp_proc_pairing_cmpl(p_cb);
    }
}