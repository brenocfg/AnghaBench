#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ len; } ;
struct airo_info {TYPE_1__ config; } ;
typedef  int /*<<< orphan*/  cfg ;
typedef  TYPE_1__ ConfigRid ;

/* Variables and functions */
 int PC4500_readrid (struct airo_info*,int /*<<< orphan*/ ,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  RID_ACTUALCONFIG ; 
 int SUCCESS ; 

__attribute__((used)) static int readConfigRid(struct airo_info *ai, int lock)
{
	int rc;
	ConfigRid cfg;

	if (ai->config.len)
		return SUCCESS;

	rc = PC4500_readrid(ai, RID_ACTUALCONFIG, &cfg, sizeof(cfg), lock);
	if (rc != SUCCESS)
		return rc;

	ai->config = cfg;
	return SUCCESS;
}