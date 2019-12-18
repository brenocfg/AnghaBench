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
typedef  int /*<<< orphan*/  tSMP_INT_DATA ;
typedef  int /*<<< orphan*/  tSMP_CB ;

/* Variables and functions */
 int /*<<< orphan*/  smp_br_send_pair_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void smp_br_process_slave_keys_response(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    smp_br_send_pair_response(p_cb, NULL);
}