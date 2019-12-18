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
struct TYPE_4__ {int /*<<< orphan*/  layer_specific; int /*<<< orphan*/  event; } ;
struct TYPE_5__ {char* str; TYPE_1__ hdr; void* uint32_val2; void* uint32_val1; int /*<<< orphan*/  uint8_val; } ;
typedef  TYPE_2__ tBTA_HF_CLIENT_DATA_VAL ;
typedef  int /*<<< orphan*/  tBTA_HF_CLIENT_AT_CMD_TYPE ;
typedef  void* UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int BTA_HF_CLIENT_NUMBER_LEN ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_SEND_AT_CMD_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

void BTA_HfClientSendAT(UINT16 handle, tBTA_HF_CLIENT_AT_CMD_TYPE at, UINT32 val1, UINT32 val2, const char *str)
{
    tBTA_HF_CLIENT_DATA_VAL  *p_buf;

    if ((p_buf = (tBTA_HF_CLIENT_DATA_VAL *) osi_malloc(sizeof(tBTA_HF_CLIENT_DATA_VAL))) != NULL) {
        p_buf->hdr.event = BTA_HF_CLIENT_SEND_AT_CMD_EVT;
        p_buf->uint8_val = at;
        p_buf->uint32_val1 = val1;
        p_buf->uint32_val2 = val2;

        if (str) {
            strlcpy(p_buf->str, str, BTA_HF_CLIENT_NUMBER_LEN + 1);
            p_buf->str[BTA_HF_CLIENT_NUMBER_LEN] = '\0';
        } else {
            p_buf->str[0] = '\0';
        }

        p_buf->hdr.layer_specific = handle;
        bta_sys_sendmsg(p_buf);
    }
}