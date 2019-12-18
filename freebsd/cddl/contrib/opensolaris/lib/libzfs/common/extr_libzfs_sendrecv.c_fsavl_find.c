#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_4__ {char* fn_snapname; int /*<<< orphan*/ * fn_nvfs; int /*<<< orphan*/  fn_guid; } ;
typedef  TYPE_1__ fsavl_node_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static nvlist_t *
fsavl_find(avl_tree_t *avl, uint64_t snapguid, char **snapname)
{
	fsavl_node_t fn_find;
	fsavl_node_t *fn;

	fn_find.fn_guid = snapguid;

	fn = avl_find(avl, &fn_find, NULL);
	if (fn) {
		if (snapname)
			*snapname = fn->fn_snapname;
		return (fn->fn_nvfs);
	}
	return (NULL);
}