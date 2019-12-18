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
struct zfcp_fsf_req {struct fsf_status_read_buffer* data; } ;
struct fsf_status_read_buffer {int status_subtype; int /*<<< orphan*/  payload; } ;
struct fsf_link_down_info {int dummy; } ;

/* Variables and functions */
#define  FSF_STATUS_READ_SUB_FDISC_FAILED 130 
#define  FSF_STATUS_READ_SUB_FIRMWARE_UPDATE 129 
#define  FSF_STATUS_READ_SUB_NO_PHYSICAL_LINK 128 
 int /*<<< orphan*/  zfcp_fsf_link_down_info_eval (struct zfcp_fsf_req*,char*,struct fsf_link_down_info*) ; 

__attribute__((used)) static void zfcp_fsf_status_read_link_down(struct zfcp_fsf_req *req)
{
	struct fsf_status_read_buffer *sr_buf = req->data;
	struct fsf_link_down_info *ldi =
		(struct fsf_link_down_info *) &sr_buf->payload;

	switch (sr_buf->status_subtype) {
	case FSF_STATUS_READ_SUB_NO_PHYSICAL_LINK:
		zfcp_fsf_link_down_info_eval(req, "fssrld1", ldi);
		break;
	case FSF_STATUS_READ_SUB_FDISC_FAILED:
		zfcp_fsf_link_down_info_eval(req, "fssrld2", ldi);
		break;
	case FSF_STATUS_READ_SUB_FIRMWARE_UPDATE:
		zfcp_fsf_link_down_info_eval(req, "fssrld3", NULL);
	};
}