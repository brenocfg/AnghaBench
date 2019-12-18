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
struct pxa_ep {int /*<<< orphan*/  dev; } ;
struct pxa27x_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN_STATUS_STAGE ; 
 int /*<<< orphan*/  ep_end_in_req (struct pxa_ep*,struct pxa27x_request*) ; 
 int /*<<< orphan*/  set_ep0state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep0_end_in_req(struct pxa_ep *ep, struct pxa27x_request *req)
{
	set_ep0state(ep->dev, IN_STATUS_STAGE);
	ep_end_in_req(ep, req);
}