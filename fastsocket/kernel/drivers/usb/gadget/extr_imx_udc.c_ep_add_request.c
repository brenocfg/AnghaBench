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
struct imx_request {int in_use; int /*<<< orphan*/  queue; } ;
struct imx_ep_struct {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ep_add_request(struct imx_ep_struct *imx_ep,
							struct imx_request *req)
{
	if (unlikely(!req))
		return;

	req->in_use = 1;
	list_add_tail(&req->queue, &imx_ep->queue);
}