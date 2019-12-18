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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ command_opcode_t ;
struct TYPE_3__ {int offset; scalar_t__* data; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 scalar_t__ HCI_COMMAND_COMPLETE_EVT ; 
 scalar_t__ HCI_SUCCESS ; 
 scalar_t__ NO_OPCODE_CHECKING ; 
 int /*<<< orphan*/  STREAM_SKIP_UINT8 (scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static uint8_t *read_command_complete_header(
    BT_HDR *response,
    command_opcode_t expected_opcode,
    size_t minimum_bytes_after)
{

    uint8_t *stream = response->data + response->offset;

    // Read the event header
    uint8_t event_code;
    uint8_t parameter_length;
    STREAM_TO_UINT8(event_code, stream);
    STREAM_TO_UINT8(parameter_length, stream);

    const size_t parameter_bytes_we_read_here = 4;

    // Check the event header values against what we expect
    assert(event_code == HCI_COMMAND_COMPLETE_EVT);
    assert(parameter_length >= (parameter_bytes_we_read_here + minimum_bytes_after));

    // Read the command complete header
    command_opcode_t opcode;
    uint8_t status;
    STREAM_SKIP_UINT8(stream); // skip the number of hci command packets field
    STREAM_TO_UINT16(opcode, stream);

    // Check the command complete header values against what we expect
    if (expected_opcode != NO_OPCODE_CHECKING) {
        assert(opcode == expected_opcode);
    }

    // Assume the next field is the status field
    STREAM_TO_UINT8(status, stream);

    if (status != HCI_SUCCESS) {
        return NULL;
    }

    return stream;
}