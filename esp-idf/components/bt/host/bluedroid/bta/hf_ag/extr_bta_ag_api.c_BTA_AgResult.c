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
typedef  int /*<<< orphan*/  tBTA_AG_RES_DATA ;
typedef  int /*<<< orphan*/  tBTA_AG_RES ;
struct TYPE_4__ {int /*<<< orphan*/  layer_specific; int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/  result; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_AG_API_RESULT ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_API_RESULT_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_AgResult(UINT16 handle, tBTA_AG_RES result, tBTA_AG_RES_DATA *p_data)
{
    tBTA_AG_API_RESULT  *p_buf;

    // printf("BTA_AgReslut: %d\n",result);
    
    if ((p_buf = (tBTA_AG_API_RESULT *) osi_malloc(sizeof(tBTA_AG_API_RESULT))) != NULL) {
        p_buf->hdr.event = BTA_AG_API_RESULT_EVT;
        p_buf->hdr.layer_specific = handle;
        p_buf->result = result;
        if(p_data) {
            memcpy(&p_buf->data, p_data, sizeof(p_buf->data));
        }
        bta_sys_sendmsg(p_buf);
    }
}