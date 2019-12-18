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
struct xresource {int xflag; } ;

/* Variables and functions */
 int XNRES ; 
 struct xresource* xresv ; 

__attribute__((used)) static struct xresource *xres_alloc(void) {
	struct xresource *xrp;
	int n;

	xrp = xresv;
	for (n = 0; n < XNRES; n++) {
		if (xrp->xflag == 0) {
			xrp->xflag = 1;
			return xrp;
		}
		xrp++;
	}
	return NULL;
}