#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  bda_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  p_value; } ;
struct TYPE_8__ {TYPE_2__ get_addr_list; TYPE_1__ read; } ;
typedef  TYPE_3__ tBTA_GATTC ;
struct TYPE_9__ {int act; scalar_t__ arg; } ;
typedef  TYPE_4__ btc_msg_t ;

/* Variables and functions */
#define  BTA_GATTC_GET_ADDR_LIST_EVT 131 
#define  BTA_GATTC_READ_CHAR_EVT 130 
#define  BTA_GATTC_READ_DESCR_EVT 129 
#define  BTA_GATTC_READ_MULTIPLE_EVT 128 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_gattc_free_req_data(btc_msg_t *msg)
{
    tBTA_GATTC *arg = (tBTA_GATTC *)(msg->arg);
    switch (msg->act) {
        case BTA_GATTC_READ_DESCR_EVT:
        case BTA_GATTC_READ_CHAR_EVT: 
        case BTA_GATTC_READ_MULTIPLE_EVT: {
            if (arg->read.p_value) {
                osi_free(arg->read.p_value);
            }
            break;
        }
        case BTA_GATTC_GET_ADDR_LIST_EVT: {
            if (arg->get_addr_list.bda_list) {
                osi_free(arg->get_addr_list.bda_list);
            }
            break;
        }
        default:
            break;
    }
    return;
}