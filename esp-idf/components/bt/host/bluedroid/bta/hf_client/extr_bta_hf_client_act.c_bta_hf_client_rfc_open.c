#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_HF_CLIENT_DATA ;
struct TYPE_3__ {int /*<<< orphan*/  peer_addr; } ;
struct TYPE_4__ {TYPE_1__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HF_CLIENT_SUCCESS ; 
 int /*<<< orphan*/  BTA_ID_HS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_2__ bta_hf_client_cb ; 
 int /*<<< orphan*/  bta_hf_client_cback_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_hf_client_slc_seq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_conn_open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void bta_hf_client_rfc_open(tBTA_HF_CLIENT_DATA *p_data)
{
    UNUSED(p_data);

    bta_sys_conn_open(BTA_ID_HS, 1, bta_hf_client_cb.scb.peer_addr);

    bta_hf_client_cback_open(NULL, BTA_HF_CLIENT_SUCCESS);

    /* start SLC procedure */
    bta_hf_client_slc_seq(FALSE);
}