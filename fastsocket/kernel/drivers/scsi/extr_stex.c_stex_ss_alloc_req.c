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
struct st_msg_header {int dummy; } ;
struct st_hba {int req_head; int rq_size; scalar_t__ dma_mem; } ;
struct req_msg {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct req_msg *stex_ss_alloc_req(struct st_hba *hba)
{
	return (struct req_msg *)(hba->dma_mem +
		hba->req_head * hba->rq_size + sizeof(struct st_msg_header));
}