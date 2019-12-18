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
struct dp_state {int /*<<< orphan*/  stat; int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPCD_LS02 ; 
 int nv_rdaux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dp_link_train_update(struct dp_state *dp, u32 delay)
{
	int ret;

	udelay(delay);

	ret = nv_rdaux(dp->aux, DPCD_LS02, dp->stat, 6);
	if (ret)
		return ret;

	DBG("status %*ph\n", 6, dp->stat);
	return 0;
}