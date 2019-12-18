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
typedef  int /*<<< orphan*/  tBTA_HF_CLIENT_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HF_CLIENT_SCO_CI_DATA_E ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_hf_client_sco_event (int /*<<< orphan*/ ) ; 

void bta_hf_client_ci_sco_data(tBTA_HF_CLIENT_DATA *p_data)
{
    UNUSED(p_data);
    bta_hf_client_sco_event(BTA_HF_CLIENT_SCO_CI_DATA_E);
}