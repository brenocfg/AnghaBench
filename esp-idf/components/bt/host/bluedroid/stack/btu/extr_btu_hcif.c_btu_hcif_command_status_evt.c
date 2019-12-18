#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {void* context; TYPE_2__* command; int /*<<< orphan*/  status; int /*<<< orphan*/  callback; } ;
typedef  TYPE_1__ command_status_hack_t ;
struct TYPE_7__ {int /*<<< orphan*/  event; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_POST_TO_TASK_NO_GOOD_HORRIBLE_HACK ; 
 int /*<<< orphan*/  OSI_THREAD_MAX_TIMEOUT ; 
 int /*<<< orphan*/  SIG_BTU_HCI_MSG ; 
 int /*<<< orphan*/  btu_hcif_command_status_evt_on_task ; 
 int /*<<< orphan*/  btu_task_post (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* osi_calloc (int) ; 

__attribute__((used)) static void btu_hcif_command_status_evt(uint8_t status, BT_HDR *command, void *context)
{
    BT_HDR *event = osi_calloc(sizeof(BT_HDR) + sizeof(command_status_hack_t));
    command_status_hack_t *hack = (command_status_hack_t *)&event->data[0];

    hack->callback = btu_hcif_command_status_evt_on_task;
    hack->status = status;
    hack->command = command;
    hack->context = context;

    event->event = BTU_POST_TO_TASK_NO_GOOD_HORRIBLE_HACK;

    btu_task_post(SIG_BTU_HCI_MSG, event, OSI_THREAD_MAX_TIMEOUT);
}