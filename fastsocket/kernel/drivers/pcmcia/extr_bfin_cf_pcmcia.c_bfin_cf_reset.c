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
 int /*<<< orphan*/  CF_ATASEL_DIS ; 
 int /*<<< orphan*/  CF_ATASEL_ENA ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bfin_cf_reset(void)
{
	outw(0, CF_ATASEL_ENA);
	mdelay(200);
	outw(0, CF_ATASEL_DIS);

	return 0;
}