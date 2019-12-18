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
struct isci_remote_device {int /*<<< orphan*/  rnc; int /*<<< orphan*/  sm; scalar_t__ started_request_count; struct isci_port* owning_port; } ;
struct isci_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX ; 
 int /*<<< orphan*/  SCI_DEV_INITIAL ; 
 int /*<<< orphan*/  sci_init_sm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_remote_device_state_table ; 
 int /*<<< orphan*/  sci_remote_node_context_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sci_remote_device_construct(struct isci_port *iport,
				  struct isci_remote_device *idev)
{
	idev->owning_port = iport;
	idev->started_request_count = 0;

	sci_init_sm(&idev->sm, sci_remote_device_state_table, SCI_DEV_INITIAL);

	sci_remote_node_context_construct(&idev->rnc,
					       SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX);
}