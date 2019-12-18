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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_BLE_READ_DEFAULT_DATA_LENGTH ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_command_complete_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void parse_ble_read_suggested_default_data_length_response(
    BT_HDR *response,
    uint16_t *ble_default_packet_length_ptr,
    uint16_t *ble_default_packet_txtime_ptr)
{

    uint8_t *stream = read_command_complete_header(response, HCI_BLE_READ_DEFAULT_DATA_LENGTH, 2 /* bytes after */);
    STREAM_TO_UINT16(*ble_default_packet_length_ptr, stream);
    STREAM_TO_UINT16(*ble_default_packet_txtime_ptr, stream);
    osi_free(response);
}