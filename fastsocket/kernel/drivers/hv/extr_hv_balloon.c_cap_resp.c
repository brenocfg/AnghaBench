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
struct hv_dynmem_device {int /*<<< orphan*/  host_event; int /*<<< orphan*/  state; } ;
struct dm_capabilities_resp_msg {int /*<<< orphan*/  is_accepted; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_INIT_ERROR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void cap_resp(struct hv_dynmem_device *dm,
			struct dm_capabilities_resp_msg *cap_resp)
{
	if (!cap_resp->is_accepted) {
		pr_info("Capabilities not accepted by host\n");
		dm->state = DM_INIT_ERROR;
	}
	complete(&dm->host_event);
}