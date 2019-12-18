#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_HF_CLIENT_AT_RESULT_TYPE ;
struct TYPE_5__ {int /*<<< orphan*/  cme; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ tBTA_HF_CLIENT_AT_RESULT ;
typedef  int /*<<< orphan*/  evt ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_6__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HF_CLIENT_AT_RESULT_EVT ; 
 TYPE_4__ bta_hf_client_cb ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

void bta_hf_client_at_result(tBTA_HF_CLIENT_AT_RESULT_TYPE type, UINT16 cme)
{
    tBTA_HF_CLIENT_AT_RESULT evt;

    memset(&evt, 0, sizeof(evt));

    evt.type = type;
    evt.cme = cme;

    (*bta_hf_client_cb.p_cback)(BTA_HF_CLIENT_AT_RESULT_EVT, &evt);
}