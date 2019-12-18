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
struct ocfs2_extent_tree {int (* et_root_journal_access ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  et_root_bh; int /*<<< orphan*/  et_ci; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int ocfs2_et_root_journal_access(handle_t *handle,
					       struct ocfs2_extent_tree *et,
					       int type)
{
	return et->et_root_journal_access(handle, et->et_ci, et->et_root_bh,
					  type);
}