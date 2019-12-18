#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_data; } ;
struct TYPE_7__ {TYPE_1__ req_data; } ;
typedef  TYPE_2__ tBTA_GATTS ;
struct TYPE_8__ {int act; } ;
typedef  TYPE_3__ btc_msg_t ;

/* Variables and functions */
#define  BTA_GATTS_CONF_EVT 132 
#define  BTA_GATTS_EXEC_WRITE_EVT 131 
#define  BTA_GATTS_MTU_EVT 130 
#define  BTA_GATTS_READ_EVT 129 
#define  BTA_GATTS_WRITE_EVT 128 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_gatts_cb_param_copy_free(btc_msg_t *msg, tBTA_GATTS *p_data)
{
    uint16_t event = msg->act;

    switch (event) {
    case BTA_GATTS_READ_EVT:
    case BTA_GATTS_WRITE_EVT:
    case BTA_GATTS_EXEC_WRITE_EVT:
    case BTA_GATTS_MTU_EVT:
        if (p_data && p_data->req_data.p_data) {
            osi_free(p_data->req_data.p_data);
        }
        break;
    case BTA_GATTS_CONF_EVT:
        break;
    default:
        break;
    }
}