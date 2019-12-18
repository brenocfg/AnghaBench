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
struct svc_xprt {int /*<<< orphan*/  xpt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  XPT_BUSY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_xprt_enqueue (struct svc_xprt*) ; 
 int /*<<< orphan*/  svc_xprt_get (struct svc_xprt*) ; 
 int /*<<< orphan*/  svc_xprt_put (struct svc_xprt*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void svc_xprt_received(struct svc_xprt *xprt)
{
	BUG_ON(!test_bit(XPT_BUSY, &xprt->xpt_flags));
	/* As soon as we clear busy, the xprt could be closed and
	 * 'put', so we need a reference to call svc_xprt_enqueue with:
	 */
	svc_xprt_get(xprt);
	clear_bit(XPT_BUSY, &xprt->xpt_flags);
	svc_xprt_enqueue(xprt);
	svc_xprt_put(xprt);
}