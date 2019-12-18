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
typedef  int /*<<< orphan*/  u32 ;
struct ipath_devdata {int /*<<< orphan*/  (* ipath_f_set_ib_cfg ) (struct ipath_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IPATH_IB_CFG_LWID_ENB ; 
 int /*<<< orphan*/  stub1 (struct ipath_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_link_width_enabled(struct ipath_devdata *dd, u32 w)
{
	(void) dd->ipath_f_set_ib_cfg(dd, IPATH_IB_CFG_LWID_ENB, w);
}