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
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  btm_sco_process_num_completed_pkts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2c_link_process_num_completed_pkts (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btu_hcif_num_compl_data_pkts_evt (UINT8 *p)
{
    /* Process for L2CAP and SCO */
    l2c_link_process_num_completed_pkts (p);

    /* Send on to SCO */
#if (BTM_SCO_HCI_INCLUDED == TRUE) && (BTM_SCO_INCLUDED == TRUE)
    btm_sco_process_num_completed_pkts (p);
#endif
}