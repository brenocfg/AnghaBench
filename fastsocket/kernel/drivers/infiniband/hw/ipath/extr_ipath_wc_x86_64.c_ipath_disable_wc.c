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
struct ipath_devdata {scalar_t__ ipath_wc_cookie; int /*<<< orphan*/  ipath_wc_len; int /*<<< orphan*/  ipath_wc_base; TYPE_1__* pcidev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*) ; 
 int mtrr_del (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ipath_disable_wc(struct ipath_devdata *dd)
{
	if (dd->ipath_wc_cookie) {
		int r;
		ipath_cdbg(VERBOSE, "undoing WCCOMB on pio buffers\n");
		r = mtrr_del(dd->ipath_wc_cookie, dd->ipath_wc_base,
			     dd->ipath_wc_len);
		if (r < 0)
			dev_info(&dd->pcidev->dev,
				 "mtrr_del(%lx, %lx, %lx) failed: %d\n",
				 dd->ipath_wc_cookie, dd->ipath_wc_base,
				 dd->ipath_wc_len, r);
		dd->ipath_wc_cookie = 0; /* even on failure */
	}
}