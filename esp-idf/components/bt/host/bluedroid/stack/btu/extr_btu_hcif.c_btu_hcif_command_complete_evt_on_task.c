#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  command_opcode_t ;
struct TYPE_5__ {TYPE_2__* response; int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ command_complete_hack_t ;
struct TYPE_6__ {int offset; scalar_t__ len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btu_hcif_hdl_command_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (TYPE_2__*) ; 

__attribute__((used)) static void btu_hcif_command_complete_evt_on_task(BT_HDR *event)
{
    command_complete_hack_t *hack = (command_complete_hack_t *)&event->data[0];

    command_opcode_t opcode;
    uint8_t *stream = hack->response->data + hack->response->offset + 3; // 2 to skip the event headers, 1 to skip the command credits
    STREAM_TO_UINT16(opcode, stream);

    btu_hcif_hdl_command_complete(
        opcode,
        stream,
        hack->response->len - 5, // 3 for the command complete headers, 2 for the event headers
        hack->context);

    osi_free(hack->response);
    osi_free(event);
}