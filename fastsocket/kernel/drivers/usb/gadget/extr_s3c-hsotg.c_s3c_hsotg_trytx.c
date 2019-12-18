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
struct TYPE_2__ {scalar_t__ actual; scalar_t__ length; } ;
struct s3c_hsotg_req {TYPE_1__ req; } ;
struct s3c_hsotg_ep {int /*<<< orphan*/  index; int /*<<< orphan*/  dir_in; struct s3c_hsotg_req* req; } ;
struct s3c_hsotg {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int s3c_hsotg_write_fifo (struct s3c_hsotg*,struct s3c_hsotg_ep*,struct s3c_hsotg_req*) ; 

__attribute__((used)) static int s3c_hsotg_trytx(struct s3c_hsotg *hsotg,
			   struct s3c_hsotg_ep *hs_ep)
{
	struct s3c_hsotg_req *hs_req = hs_ep->req;

	if (!hs_ep->dir_in || !hs_req)
		return 0;

	if (hs_req->req.actual < hs_req->req.length) {
		dev_dbg(hsotg->dev, "trying to write more for ep%d\n",
			hs_ep->index);
		return s3c_hsotg_write_fifo(hsotg, hs_ep, hs_req);
	}

	return 0;
}