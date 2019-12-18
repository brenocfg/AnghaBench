#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  service; } ;
typedef  TYPE_2__ tBTA_UTL_COD ;
typedef  int /*<<< orphan*/  tBTA_HF_CLIENT_DATA ;
struct TYPE_5__ {int /*<<< orphan*/  deregister; } ;
struct TYPE_7__ {TYPE_1__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_UTL_CLR_COD_SERVICE_CLASS ; 
 int /*<<< orphan*/  BTM_COD_SERVICE_AUDIO ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ bta_hf_client_cb ; 
 int /*<<< orphan*/  bta_hf_client_close_server () ; 
 int /*<<< orphan*/  bta_hf_client_del_record (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_hf_client_scb_disable () ; 
 int /*<<< orphan*/  utl_set_device_class (TYPE_2__*,int /*<<< orphan*/ ) ; 

void bta_hf_client_deregister(tBTA_HF_CLIENT_DATA *p_data)
{
    tBTA_UTL_COD   cod;

    bta_hf_client_cb.scb.deregister = TRUE;

    /* Clear the Audio service class bit */
    cod.service = BTM_COD_SERVICE_AUDIO;
    utl_set_device_class(&cod, BTA_UTL_CLR_COD_SERVICE_CLASS);

    /* remove sdp record */
    bta_hf_client_del_record(p_data);

    /* remove rfcomm server */
    bta_hf_client_close_server();

    /* disable */
    bta_hf_client_scb_disable();
}