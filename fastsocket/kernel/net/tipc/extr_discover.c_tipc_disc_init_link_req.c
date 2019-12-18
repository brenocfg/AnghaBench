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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_media_addr {int dummy; } ;
struct link_req {int /*<<< orphan*/  timer_intv; int /*<<< orphan*/  timer; struct bearer* bearer; int /*<<< orphan*/  dest; int /*<<< orphan*/  buf; } ;
struct bearer {int dummy; } ;
typedef  int /*<<< orphan*/  Handler ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_REQ_MSG ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  TIPC_LINK_REQ_INIT ; 
 scalar_t__ disc_timeout ; 
 int /*<<< orphan*/  k_init_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  k_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct link_req*) ; 
 struct link_req* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct tipc_media_addr const*,int) ; 
 int /*<<< orphan*/  tipc_disc_init_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bearer*) ; 

struct link_req *tipc_disc_init_link_req(struct bearer *b_ptr,
					 const struct tipc_media_addr *dest,
					 u32 dest_domain,
					 u32 req_links)
{
	struct link_req *req;

	req = kmalloc(sizeof(*req), GFP_ATOMIC);
	if (!req)
		return NULL;

	req->buf = tipc_disc_init_msg(DSC_REQ_MSG, req_links, dest_domain, b_ptr);
	if (!req->buf) {
		kfree(req);
		return NULL;
	}

	memcpy(&req->dest, dest, sizeof(*dest));
	req->bearer = b_ptr;
	req->timer_intv = TIPC_LINK_REQ_INIT;
	k_init_timer(&req->timer, (Handler)disc_timeout, (unsigned long)req);
	k_start_timer(&req->timer, req->timer_intv);
	return req;
}