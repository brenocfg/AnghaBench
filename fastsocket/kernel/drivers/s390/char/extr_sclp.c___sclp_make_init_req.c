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
typedef  void* u32 ;
struct sclp_req {int dummy; } ;
struct TYPE_4__ {int length; } ;
struct init_sccb {int mask_length; scalar_t__ sclp_send_mask; scalar_t__ sclp_receive_mask; void* send_mask; void* receive_mask; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  sccb_mask_t ;
struct TYPE_5__ {struct init_sccb* sccb; int /*<<< orphan*/ * callback_data; int /*<<< orphan*/ * callback; scalar_t__ start_count; int /*<<< orphan*/  status; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCLP_CMDW_WRITE_EVENT_MASK ; 
 int /*<<< orphan*/  SCLP_REQ_FILLED ; 
 int /*<<< orphan*/  clear_page (struct init_sccb*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ sclp_init_req ; 
 scalar_t__ sclp_init_sccb ; 

__attribute__((used)) static inline void
__sclp_make_init_req(u32 receive_mask, u32 send_mask)
{
	struct init_sccb *sccb;

	sccb = (struct init_sccb *) sclp_init_sccb;
	clear_page(sccb);
	memset(&sclp_init_req, 0, sizeof(struct sclp_req));
	sclp_init_req.command = SCLP_CMDW_WRITE_EVENT_MASK;
	sclp_init_req.status = SCLP_REQ_FILLED;
	sclp_init_req.start_count = 0;
	sclp_init_req.callback = NULL;
	sclp_init_req.callback_data = NULL;
	sclp_init_req.sccb = sccb;
	sccb->header.length = sizeof(struct init_sccb);
	sccb->mask_length = sizeof(sccb_mask_t);
	sccb->receive_mask = receive_mask;
	sccb->send_mask = send_mask;
	sccb->sclp_receive_mask = 0;
	sccb->sclp_send_mask = 0;
}