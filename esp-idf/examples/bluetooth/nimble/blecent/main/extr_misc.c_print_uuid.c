#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ble_uuid_t ;

/* Variables and functions */
 int BLE_UUID_STR_LEN ; 
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  MODLOG_DFLT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ble_uuid_to_str (int /*<<< orphan*/  const*,char*) ; 

void
print_uuid(const ble_uuid_t *uuid)
{
    char buf[BLE_UUID_STR_LEN];

    MODLOG_DFLT(DEBUG, "%s", ble_uuid_to_str(uuid, buf));
}