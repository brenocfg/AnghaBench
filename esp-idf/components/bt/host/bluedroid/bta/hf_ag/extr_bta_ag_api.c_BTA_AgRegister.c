#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_SERVICE_MASK ;
typedef  int /*<<< orphan*/  tBTA_SEC ;
typedef  int /*<<< orphan*/  tBTA_AG_FEAT ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {scalar_t__** p_name; int /*<<< orphan*/  app_id; int /*<<< orphan*/  services; int /*<<< orphan*/  sec_mask; int /*<<< orphan*/  features; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_AG_API_REGISTER ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_STRNCPY_S (scalar_t__*,int,char*,int) ; 
 int /*<<< orphan*/  BTA_AG_API_REGISTER_EVT ; 
 int BTA_AG_NUM_IDX ; 
 int BTA_SERVICE_NAME_LEN ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_AgRegister(tBTA_SERVICE_MASK services, tBTA_SEC sec_mask,tBTA_AG_FEAT features,
                  char * p_service_names[], UINT8 app_id)
{
    tBTA_AG_API_REGISTER    *p_buf;
    int                     i;

    if ((p_buf = (tBTA_AG_API_REGISTER *) osi_malloc(sizeof(tBTA_AG_API_REGISTER))) != NULL) {
        p_buf->hdr.event = BTA_AG_API_REGISTER_EVT;
        p_buf->features = features;
        p_buf->sec_mask = sec_mask;
        p_buf->services = services;
        p_buf->app_id = app_id;
        for (i = 0; i < BTA_AG_NUM_IDX; i++) {
            if(p_service_names[i]) {
                BCM_STRNCPY_S(p_buf->p_name[i], BTA_SERVICE_NAME_LEN+1, p_service_names[i], BTA_SERVICE_NAME_LEN);
                p_buf->p_name[i][BTA_SERVICE_NAME_LEN] = 0;
            } else {
                p_buf->p_name[i][0] = 0;
            }
        }
        bta_sys_sendmsg(p_buf);
    }
}