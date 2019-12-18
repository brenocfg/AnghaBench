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
typedef  int /*<<< orphan*/  u8 ;
struct fsl_udc {int dummy; } ;
struct fsl_ep {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 struct fsl_ep* get_ep_by_pipe (struct fsl_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuke (struct fsl_ep*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_reset_ep_queue(struct fsl_udc *udc, u8 pipe)
{
	struct fsl_ep *ep = get_ep_by_pipe(udc, pipe);

	if (ep->name)
		nuke(ep, -ESHUTDOWN);
}