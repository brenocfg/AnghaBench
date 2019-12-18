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
 int /*<<< orphan*/  HCI_BLE_READ_BUFFER_SIZE ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_command_complete_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void parse_ble_read_buffer_size_response(
    BT_HDR *response,
    uint16_t *data_size_ptr,
    uint8_t *acl_buffer_count_ptr)
{

    uint8_t *stream = read_command_complete_header(response, HCI_BLE_READ_BUFFER_SIZE, 3 /* bytes after */);
    assert(stream != NULL);
    STREAM_TO_UINT16(*data_size_ptr, stream);
    STREAM_TO_UINT8(*acl_buffer_count_ptr, stream);

    osi_free(response);
}