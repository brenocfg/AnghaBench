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
struct TYPE_3__ {int /*<<< orphan*/ * p_disc_db; } ;
struct TYPE_4__ {TYPE_1__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_2__ bta_hf_client_cb ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 

void bta_hf_client_free_db(tBTA_HF_CLIENT_DATA *p_data)
{
    UNUSED(p_data);

    if (bta_hf_client_cb.scb.p_disc_db != NULL) {
        osi_free(bta_hf_client_cb.scb.p_disc_db);
        bta_hf_client_cb.scb.p_disc_db = NULL;
    }
}