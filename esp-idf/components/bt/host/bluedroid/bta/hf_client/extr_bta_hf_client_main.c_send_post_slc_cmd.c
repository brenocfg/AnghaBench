#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  current_cmd; } ;
struct TYPE_5__ {TYPE_1__ at_cb; } ;
struct TYPE_6__ {TYPE_2__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HF_CLIENT_AT_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ bta_hf_client_cb ; 
 int /*<<< orphan*/  bta_hf_client_send_at_bia () ; 
 int /*<<< orphan*/  bta_hf_client_send_at_btrh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_hf_client_send_at_ccwa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_hf_client_send_at_clip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_hf_client_send_at_cmee (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_hf_client_send_at_cops (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_post_slc_cmd(void)
{
    bta_hf_client_cb.scb.at_cb.current_cmd = BTA_HF_CLIENT_AT_NONE;

    bta_hf_client_send_at_bia();
    bta_hf_client_send_at_ccwa(TRUE);
    bta_hf_client_send_at_cmee(TRUE);
    bta_hf_client_send_at_cops(FALSE);
    bta_hf_client_send_at_btrh(TRUE, 0);
    bta_hf_client_send_at_clip(TRUE);
}