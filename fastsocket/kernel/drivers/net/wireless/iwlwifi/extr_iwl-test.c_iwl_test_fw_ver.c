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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_test {TYPE_2__* trans; TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  op_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_fw_ver ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 iwl_test_fw_ver(struct iwl_test *tst)
{
	return tst->ops->get_fw_ver(tst->trans->op_mode);
}