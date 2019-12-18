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
struct coalition_resource_usage {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COALITION_INFO_RESOURCE_USAGE ; 
 int __coalition_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct coalition_resource_usage*,size_t*) ; 

int coalition_info_resource_usage(uint64_t cid, struct coalition_resource_usage *cru, size_t sz)
{
	return __coalition_info(COALITION_INFO_RESOURCE_USAGE, &cid, cru, &sz);
}