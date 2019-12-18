#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iwl_trans {TYPE_1__* ops; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int (* dbgfs_register ) (struct iwl_trans*,struct dentry*) ;} ;

/* Variables and functions */
 int stub1 (struct iwl_trans*,struct dentry*) ; 

__attribute__((used)) static inline int iwl_trans_dbgfs_register(struct iwl_trans *trans,
					   struct dentry *dir)
{
	return trans->ops->dbgfs_register(trans, dir);
}