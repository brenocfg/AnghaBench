#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct se_cmd {TYPE_2__* se_dev; } ;
struct TYPE_3__ {int block_size; } ;
struct TYPE_4__ {TYPE_1__ dev_attrib; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 sbc_get_size(struct se_cmd *cmd, u32 sectors)
{
	return cmd->se_dev->dev_attrib.block_size * sectors;
}