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
struct zfcp_fsf_req {scalar_t__ data; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct fsf_status_read_buffer {TYPE_1__ payload; } ;
struct fcp_logo {int /*<<< orphan*/  nport_wwpn; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfcp_fc_incoming_wwpn (struct zfcp_fsf_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_fc_incoming_logo(struct zfcp_fsf_req *req)
{
	struct fsf_status_read_buffer *status_buffer =
		(struct fsf_status_read_buffer *)req->data;
	struct fcp_logo *els_logo =
		(struct fcp_logo *) status_buffer->payload.data;

	zfcp_fc_incoming_wwpn(req, els_logo->nport_wwpn);
}