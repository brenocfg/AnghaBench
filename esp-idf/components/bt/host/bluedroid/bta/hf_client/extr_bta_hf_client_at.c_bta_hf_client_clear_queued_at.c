#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* next; } ;
typedef  TYPE_3__ tBTA_HF_CLIENT_AT_QCMD ;
struct TYPE_6__ {TYPE_3__* queued_cmd; } ;
struct TYPE_7__ {TYPE_1__ at_cb; } ;
struct TYPE_9__ {TYPE_2__ scb; } ;

/* Variables and functions */
 TYPE_5__ bta_hf_client_cb ; 
 int /*<<< orphan*/  osi_free (TYPE_3__*) ; 

__attribute__((used)) static void bta_hf_client_clear_queued_at(void)
{
    tBTA_HF_CLIENT_AT_QCMD *cur = bta_hf_client_cb.scb.at_cb.queued_cmd;
    tBTA_HF_CLIENT_AT_QCMD *next;

    while (cur != NULL) {
        next = cur->next;
        osi_free(cur);
        cur = next;
    }

    bta_hf_client_cb.scb.at_cb.queued_cmd = NULL;
}