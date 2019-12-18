#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_BG_CONN_DEV ;
struct TYPE_2__ {int /*<<< orphan*/  bgconn_dev; } ;

/* Variables and functions */
 int GATT_MAX_BG_CONN_DEV ; 
 TYPE_1__ gatt_cb ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void gatt_reset_bgdev_list(void)
{
    memset(&gatt_cb.bgconn_dev, 0 , sizeof(tGATT_BG_CONN_DEV)*GATT_MAX_BG_CONN_DEV);

}