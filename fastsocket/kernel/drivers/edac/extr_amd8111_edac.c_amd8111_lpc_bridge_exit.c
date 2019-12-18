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
struct amd8111_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEGACY_NR_PORTS ; 
 int /*<<< orphan*/  REG_AT_COMPAT ; 
 scalar_t__ legacy_io_res ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amd8111_lpc_bridge_exit(struct amd8111_dev_info *dev_info)
{
	if (legacy_io_res)
		release_region(REG_AT_COMPAT, LEGACY_NR_PORTS);
}