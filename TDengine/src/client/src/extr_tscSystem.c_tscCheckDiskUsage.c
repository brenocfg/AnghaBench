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

/* Variables and functions */
 int /*<<< orphan*/  taosGetDisk () ; 
 int /*<<< orphan*/  taosTmrReset (void (*) (void*,void*),int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tscCheckDiskUsageTmr ; 
 int /*<<< orphan*/  tscTmr ; 

void tscCheckDiskUsage(void *para, void *unused) {
  taosGetDisk();
  taosTmrReset(tscCheckDiskUsage, 1000, NULL, tscTmr, &tscCheckDiskUsageTmr);
}