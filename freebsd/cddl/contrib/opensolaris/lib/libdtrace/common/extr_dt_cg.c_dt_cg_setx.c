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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dt_irlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_LBL_NONE ; 
 int /*<<< orphan*/  dt_cg_xsetx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dt_cg_setx(dt_irlist_t *dlp, int reg, uint64_t x)
{
	dt_cg_xsetx(dlp, NULL, DT_LBL_NONE, reg, x);
}