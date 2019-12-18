#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bda; int /*<<< orphan*/  transport; void* connected; int /*<<< orphan*/  conn_id; void* in_use; } ;
typedef  TYPE_1__ tGATT_PROFILE_CLCB ;
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_5__ {TYPE_1__* profile_clcb; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ GATT_MAX_APPS ; 
 void* TRUE ; 
 TYPE_3__ gatt_cb ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tGATT_PROFILE_CLCB *gatt_profile_clcb_alloc (UINT16 conn_id, BD_ADDR bda, tBT_TRANSPORT tranport)
{
    UINT8                   i_clcb = 0;
    tGATT_PROFILE_CLCB      *p_clcb = NULL;

    for (i_clcb = 0, p_clcb = gatt_cb.profile_clcb; i_clcb < GATT_MAX_APPS; i_clcb++, p_clcb++) {
        if (!p_clcb->in_use) {
            p_clcb->in_use      = TRUE;
            p_clcb->conn_id     = conn_id;
            p_clcb->connected   = TRUE;
            p_clcb->transport   = tranport;
            memcpy (p_clcb->bda, bda, BD_ADDR_LEN);
            break;
        }
    }
    if (i_clcb < GATT_MAX_APPS) {
        return p_clcb;
    }

    return NULL;
}