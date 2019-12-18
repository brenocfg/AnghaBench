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
typedef  int /*<<< orphan*/  u16 ;
struct airo_info {int dummy; } ;

/* Variables and functions */
 int PC4500_writerid (struct airo_info*,int /*<<< orphan*/ ,void const*,int,int) ; 
 int /*<<< orphan*/  disable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  enable_MAC (struct airo_info*,int) ; 

__attribute__((used)) static int do_writerid( struct airo_info *ai, u16 rid, const void *rid_data,
			int len, int dummy ) {
	int rc;

	disable_MAC(ai, 1);
	rc = PC4500_writerid(ai, rid, rid_data, len, 1);
	enable_MAC(ai, 1);
	return rc;
}