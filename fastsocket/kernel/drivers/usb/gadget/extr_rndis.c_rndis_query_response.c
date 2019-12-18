#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rndis_params {int /*<<< orphan*/  v; int /*<<< orphan*/  (* resp_avail ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {scalar_t__ buf; } ;
typedef  TYPE_1__ rndis_resp_t ;
struct TYPE_8__ {int /*<<< orphan*/  InformationBufferLength; int /*<<< orphan*/  InformationBufferOffset; int /*<<< orphan*/  OID; int /*<<< orphan*/  RequestID; } ;
typedef  TYPE_2__ rndis_query_msg_type ;
struct TYPE_9__ {void* Status; void* InformationBufferOffset; void* InformationBufferLength; void* MessageLength; int /*<<< orphan*/  RequestID; void* MessageType; } ;
typedef  TYPE_3__ rndis_query_cmplt_type ;
typedef  int /*<<< orphan*/  oid_supported_list ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTSUPP ; 
 int REMOTE_NDIS_QUERY_CMPLT ; 
 int RNDIS_STATUS_NOT_SUPPORTED ; 
 int RNDIS_STATUS_SUCCESS ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ gen_ndis_query_resp (int,int,int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* rndis_add_response (int,int) ; 
 struct rndis_params* rndis_per_dev_params ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rndis_query_response (int configNr, rndis_query_msg_type *buf)
{
	rndis_query_cmplt_type *resp;
	rndis_resp_t            *r;
	struct rndis_params	*params = rndis_per_dev_params + configNr;

	/* pr_debug("%s: OID = %08X\n", __func__, cpu_to_le32(buf->OID)); */
	if (!params->dev)
		return -ENOTSUPP;

	/*
	 * we need more memory:
	 * gen_ndis_query_resp expects enough space for
	 * rndis_query_cmplt_type followed by data.
	 * oid_supported_list is the largest data reply
	 */
	r = rndis_add_response (configNr,
		sizeof (oid_supported_list) + sizeof(rndis_query_cmplt_type));
	if (!r)
		return -ENOMEM;
	resp = (rndis_query_cmplt_type *) r->buf;

	resp->MessageType = cpu_to_le32 (REMOTE_NDIS_QUERY_CMPLT);
	resp->RequestID = buf->RequestID; /* Still LE in msg buffer */

	if (gen_ndis_query_resp (configNr, le32_to_cpu (buf->OID),
			le32_to_cpu(buf->InformationBufferOffset)
					+ 8 + (u8 *) buf,
			le32_to_cpu(buf->InformationBufferLength),
			r)) {
		/* OID not supported */
		resp->Status = cpu_to_le32 (
				RNDIS_STATUS_NOT_SUPPORTED);
		resp->MessageLength = cpu_to_le32 (sizeof *resp);
		resp->InformationBufferLength = cpu_to_le32 (0);
		resp->InformationBufferOffset = cpu_to_le32 (0);
	} else
		resp->Status = cpu_to_le32 (RNDIS_STATUS_SUCCESS);

	params->resp_avail(params->v);
	return 0;
}