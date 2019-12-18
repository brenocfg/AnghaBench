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
struct ipath_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipath_dbg (char*) ; 

__attribute__((used)) static int ipath_setup_ht_reset(struct ipath_devdata *dd)
{
	ipath_dbg("No reset possible for this InfiniPath hardware\n");
	return 0;
}