#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hv_dynmem_device {scalar_t__ next_version; int /*<<< orphan*/  host_event; int /*<<< orphan*/  state; TYPE_3__* dev; } ;
struct dm_version_response {scalar_t__ is_accepted; } ;
struct TYPE_5__ {int /*<<< orphan*/  version; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  type; } ;
struct dm_version_request {int is_last_attempt; TYPE_2__ version; TYPE_1__ hdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_INIT_ERROR ; 
 int /*<<< orphan*/  DM_VERSION_REQUEST ; 
 int /*<<< orphan*/  DYNMEM_PROTOCOL_VERSION_WIN7 ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dm_version_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trans_id ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,struct dm_version_request*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void version_resp(struct hv_dynmem_device *dm,
			struct dm_version_response *vresp)
{
	struct dm_version_request version_req;
	int ret;

	if (vresp->is_accepted) {
		/*
		 * We are done; wakeup the
		 * context waiting for version
		 * negotiation.
		 */
		complete(&dm->host_event);
		return;
	}
	/*
	 * If there are more versions to try, continue
	 * with negotiations; if not
	 * shutdown the service since we are not able
	 * to negotiate a suitable version number
	 * with the host.
	 */
	if (dm->next_version == 0)
		goto version_error;

	dm->next_version = 0;
	memset(&version_req, 0, sizeof(struct dm_version_request));
	version_req.hdr.type = DM_VERSION_REQUEST;
	version_req.hdr.size = sizeof(struct dm_version_request);
	version_req.hdr.trans_id = atomic_inc_return(&trans_id);
	version_req.version.version = DYNMEM_PROTOCOL_VERSION_WIN7;
	version_req.is_last_attempt = 1;

	ret = vmbus_sendpacket(dm->dev->channel, &version_req,
				sizeof(struct dm_version_request),
				(unsigned long)NULL,
				VM_PKT_DATA_INBAND, 0);

	if (ret)
		goto version_error;

	return;

version_error:
	dm->state = DM_INIT_ERROR;
	complete(&dm->host_event);
}