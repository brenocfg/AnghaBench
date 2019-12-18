#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zfcp_fsf_req {scalar_t__ data; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  scsi_host; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct fsf_status_read_buffer {TYPE_1__ payload; int /*<<< orphan*/  d_id; scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_host_port_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_san_els (char*,int,struct zfcp_fsf_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

void zfcp_dbf_san_incoming_els(struct zfcp_fsf_req *fsf_req)
{
	struct zfcp_adapter *adapter = fsf_req->adapter;
	struct fsf_status_read_buffer *buf =
			(struct fsf_status_read_buffer *)fsf_req->data;
	int length = (int)buf->length -
		     (int)((void *)&buf->payload - (void *)buf);

	zfcp_dbf_san_els("iels", 1, fsf_req, buf->d_id,
			       fc_host_port_id(adapter->scsi_host),
			       buf->payload.data[0], (void *)buf->payload.data,
			       length);
}