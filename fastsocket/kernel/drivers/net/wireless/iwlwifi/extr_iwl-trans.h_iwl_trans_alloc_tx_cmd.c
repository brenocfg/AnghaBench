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
struct iwl_trans {int dev_cmd_headroom; int /*<<< orphan*/  dev_cmd_pool; } ;
struct iwl_device_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/ * kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct iwl_device_cmd *
iwl_trans_alloc_tx_cmd(struct iwl_trans *trans)
{
	u8 *dev_cmd_ptr = kmem_cache_alloc(trans->dev_cmd_pool, GFP_ATOMIC);

	if (unlikely(dev_cmd_ptr == NULL))
		return NULL;

	return (struct iwl_device_cmd *)
			(dev_cmd_ptr + trans->dev_cmd_headroom);
}