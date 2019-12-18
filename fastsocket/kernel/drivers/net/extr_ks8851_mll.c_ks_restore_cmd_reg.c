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
struct ks_net {int /*<<< orphan*/  hw_addr_cmd; int /*<<< orphan*/  cmd_reg_cache; int /*<<< orphan*/  cmd_reg_cache_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ks_restore_cmd_reg(struct ks_net *ks)
{
	ks->cmd_reg_cache = ks->cmd_reg_cache_int;
	iowrite16(ks->cmd_reg_cache, ks->hw_addr_cmd);
}