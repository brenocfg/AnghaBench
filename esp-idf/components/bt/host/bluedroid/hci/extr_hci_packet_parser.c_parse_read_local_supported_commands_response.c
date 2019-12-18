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
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_READ_LOCAL_SUPPORTED_CMDS ; 
 int /*<<< orphan*/  STREAM_TO_ARRAY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_command_complete_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void parse_read_local_supported_commands_response(
    BT_HDR *response,
    uint8_t *supported_commands_ptr,
    size_t supported_commands_length)
{

    uint8_t *stream = read_command_complete_header(response, HCI_READ_LOCAL_SUPPORTED_CMDS, supported_commands_length /* bytes after */);
    assert(stream != NULL);
    STREAM_TO_ARRAY(supported_commands_ptr, stream, (int)supported_commands_length);

    osi_free(response);
}