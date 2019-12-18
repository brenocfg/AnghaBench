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
struct TYPE_3__ {int /*<<< orphan*/  deregister; } ;
struct TYPE_4__ {TYPE_1__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ bta_hf_client_cb ; 
 int /*<<< orphan*/  bta_hf_client_del_record (int /*<<< orphan*/ *) ; 

void bta_hf_client_start_dereg(tBTA_HF_CLIENT_DATA *p_data)
{
    bta_hf_client_cb.scb.deregister = TRUE;

    /* remove sdp record */
    bta_hf_client_del_record(p_data);
}