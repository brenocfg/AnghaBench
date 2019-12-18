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
struct zfcp_fsf_req {scalar_t__ data; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct fsf_status_read_buffer {TYPE_1__ payload; } ;
struct TYPE_4__ {int /*<<< orphan*/  wwpn; } ;
struct fsf_plogi {TYPE_2__ serv_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfcp_fc_incoming_wwpn (struct zfcp_fsf_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_fc_incoming_plogi(struct zfcp_fsf_req *req)
{
	struct fsf_status_read_buffer *status_buffer =
		(struct fsf_status_read_buffer *)req->data;
	struct fsf_plogi *els_plogi =
		(struct fsf_plogi *) status_buffer->payload.data;

	zfcp_fc_incoming_wwpn(req, els_plogi->serv_param.wwpn);
}