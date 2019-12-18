#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  as_array; } ;
typedef  TYPE_1__ bt_device_features_t ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_BLE_READ_LOCAL_SPT_FEAT ; 
 int /*<<< orphan*/  STREAM_TO_ARRAY (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_command_complete_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void parse_ble_read_local_supported_features_response(
    BT_HDR *response,
    bt_device_features_t *supported_features)
{

    uint8_t *stream = read_command_complete_header(response, HCI_BLE_READ_LOCAL_SPT_FEAT, sizeof(bt_device_features_t) /* bytes after */);
    assert(stream != NULL);
    STREAM_TO_ARRAY(supported_features->as_array, stream, (int)sizeof(bt_device_features_t));

    osi_free(response);
}