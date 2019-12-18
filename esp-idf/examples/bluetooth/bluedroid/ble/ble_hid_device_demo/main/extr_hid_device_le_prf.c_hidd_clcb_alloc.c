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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int in_use; int connected; int /*<<< orphan*/  remote_bda; int /*<<< orphan*/  conn_id; } ;
typedef  TYPE_1__ hidd_clcb_t ;
typedef  int /*<<< orphan*/  esp_bd_addr_t ;
struct TYPE_4__ {TYPE_1__* hidd_clcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BD_ADDR_LEN ; 
 scalar_t__ HID_MAX_APPS ; 
 TYPE_2__ hidd_le_env ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hidd_clcb_alloc (uint16_t conn_id, esp_bd_addr_t bda)
{
    uint8_t                   i_clcb = 0;
    hidd_clcb_t      *p_clcb = NULL;

    for (i_clcb = 0, p_clcb= hidd_le_env.hidd_clcb; i_clcb < HID_MAX_APPS; i_clcb++, p_clcb++) {
        if (!p_clcb->in_use) {
            p_clcb->in_use      = true;
            p_clcb->conn_id     = conn_id;
            p_clcb->connected   = true;
            memcpy (p_clcb->remote_bda, bda, ESP_BD_ADDR_LEN);
            break;
        }
    }
    return;
}