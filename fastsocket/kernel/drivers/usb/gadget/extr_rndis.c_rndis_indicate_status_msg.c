#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rndis_params {scalar_t__ state; int /*<<< orphan*/  v; int /*<<< orphan*/  (* resp_avail ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ buf; } ;
typedef  TYPE_1__ rndis_resp_t ;
struct TYPE_5__ {void* StatusBufferOffset; void* StatusBufferLength; void* Status; void* MessageLength; void* MessageType; } ;
typedef  TYPE_2__ rndis_indicate_status_msg_type ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTSUPP ; 
 int REMOTE_NDIS_INDICATE_STATUS_MSG ; 
 scalar_t__ RNDIS_UNINITIALIZED ; 
 void* cpu_to_le32 (int) ; 
 TYPE_1__* rndis_add_response (int,int) ; 
 struct rndis_params* rndis_per_dev_params ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rndis_indicate_status_msg (int configNr, u32 status)
{
	rndis_indicate_status_msg_type	*resp;
	rndis_resp_t			*r;
	struct rndis_params	*params = rndis_per_dev_params + configNr;

	if (params->state == RNDIS_UNINITIALIZED)
		return -ENOTSUPP;

	r = rndis_add_response (configNr,
				sizeof (rndis_indicate_status_msg_type));
	if (!r)
		return -ENOMEM;
	resp = (rndis_indicate_status_msg_type *) r->buf;

	resp->MessageType = cpu_to_le32 (
			REMOTE_NDIS_INDICATE_STATUS_MSG);
	resp->MessageLength = cpu_to_le32 (20);
	resp->Status = cpu_to_le32 (status);
	resp->StatusBufferLength = cpu_to_le32 (0);
	resp->StatusBufferOffset = cpu_to_le32 (0);

	params->resp_avail(params->v);
	return 0;
}