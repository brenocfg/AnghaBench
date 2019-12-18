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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_trans {int /*<<< orphan*/  dev_cmd_pool; int /*<<< orphan*/ * dev_cmd_headroom; } ;
struct iwl_device_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void iwl_trans_free_tx_cmd(struct iwl_trans *trans,
					 struct iwl_device_cmd *dev_cmd)
{
	u8 *dev_cmd_ptr = (u8 *)dev_cmd - trans->dev_cmd_headroom;

	kmem_cache_free(trans->dev_cmd_pool, dev_cmd_ptr);
}