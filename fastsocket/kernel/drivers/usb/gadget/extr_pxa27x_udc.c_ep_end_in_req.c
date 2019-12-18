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
struct pxa_ep {int dummy; } ;
struct pxa27x_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  inc_ep_stats_reqs (struct pxa_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_done (struct pxa_ep*,struct pxa27x_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep_end_in_req(struct pxa_ep *ep, struct pxa27x_request *req)
{
	inc_ep_stats_reqs(ep, USB_DIR_IN);
	req_done(ep, req, 0);
}