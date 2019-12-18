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
typedef  int /*<<< orphan*/  u16 ;
struct usb_host_endpoint {struct r8a66597_pipe* hcpriv; } ;
struct urb {int /*<<< orphan*/  pipe; } ;
struct TYPE_2__ {int /*<<< orphan*/  pipenum; } ;
struct r8a66597_pipe {TYPE_1__ info; } ;

/* Variables and functions */
 scalar_t__ usb_pipeendpoint (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 r8a66597_get_pipenum(struct urb *urb, struct usb_host_endpoint *hep)
{
	struct r8a66597_pipe *pipe = hep->hcpriv;

	if (usb_pipeendpoint(urb->pipe) == 0)
		return 0;
	else
		return pipe->info.pipenum;
}