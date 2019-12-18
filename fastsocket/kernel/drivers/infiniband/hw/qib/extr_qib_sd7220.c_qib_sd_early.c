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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int EPB_GLOBAL_WR ; 
 int RXHSCTRL0 (int /*<<< orphan*/ ) ; 
 int START_EQ1 (int /*<<< orphan*/ ) ; 
 int START_EQ2 (int /*<<< orphan*/ ) ; 
 int ibsd_mod_allchnls (struct qib_devdata*,int,int,int) ; 

__attribute__((used)) static int qib_sd_early(struct qib_devdata *dd)
{
	int ret;

	ret = ibsd_mod_allchnls(dd, RXHSCTRL0(0) | EPB_GLOBAL_WR, 0xD4, 0xFF);
	if (ret < 0)
		goto bail;
	ret = ibsd_mod_allchnls(dd, START_EQ1(0) | EPB_GLOBAL_WR, 0x10, 0xFF);
	if (ret < 0)
		goto bail;
	ret = ibsd_mod_allchnls(dd, START_EQ2(0) | EPB_GLOBAL_WR, 0x30, 0xFF);
bail:
	return ret;
}