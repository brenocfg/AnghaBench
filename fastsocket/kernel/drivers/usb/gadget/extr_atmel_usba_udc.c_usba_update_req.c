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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ length; scalar_t__ actual; } ;
struct usba_request {TYPE_1__ req; } ;
struct usba_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUF_LEN ; 
 scalar_t__ USBA_BFEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usba_update_req(struct usba_ep *ep, struct usba_request *req, u32 status)
{
	req->req.actual = req->req.length - USBA_BFEXT(DMA_BUF_LEN, status);
}