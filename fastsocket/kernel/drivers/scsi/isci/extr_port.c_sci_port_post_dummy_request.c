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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct scu_task_context {scalar_t__ abort; } ;
struct isci_port {size_t physical_port_index; int /*<<< orphan*/  reserved_tag; struct isci_host* owning_controller; } ;
struct isci_host {struct scu_task_context* task_context_table; } ;

/* Variables and functions */
 size_t ISCI_TAG_TCI (int /*<<< orphan*/ ) ; 
 size_t SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT ; 
 size_t SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_TC ; 
 int /*<<< orphan*/  sci_controller_post_request (struct isci_host*,size_t) ; 

__attribute__((used)) static void sci_port_post_dummy_request(struct isci_port *iport)
{
	struct isci_host *ihost = iport->owning_controller;
	u16 tag = iport->reserved_tag;
	struct scu_task_context *tc;
	u32 command;

	tc = &ihost->task_context_table[ISCI_TAG_TCI(tag)];
	tc->abort = 0;

	command = SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_TC |
		  iport->physical_port_index << SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT |
		  ISCI_TAG_TCI(tag);

	sci_controller_post_request(ihost, command);
}