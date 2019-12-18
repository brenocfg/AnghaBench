#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct zfcp_send_els {TYPE_2__* req; int /*<<< orphan*/  d_id; TYPE_1__* adapter; } ;
struct zfcp_fsf_req {scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; } ;
struct TYPE_3__ {int /*<<< orphan*/  scsi_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_host_port_id (int /*<<< orphan*/ ) ; 
 scalar_t__ sg_virt (TYPE_2__*) ; 
 int /*<<< orphan*/  zfcp_dbf_san_els (char*,int,struct zfcp_fsf_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void zfcp_dbf_san_els_request(struct zfcp_fsf_req *fsf_req)
{
	struct zfcp_send_els *els = (struct zfcp_send_els *)fsf_req->data;

	zfcp_dbf_san_els("oels", 2, fsf_req,
			       fc_host_port_id(els->adapter->scsi_host),
			       els->d_id, *(u8 *) sg_virt(els->req),
			       sg_virt(els->req), els->req->length);
}