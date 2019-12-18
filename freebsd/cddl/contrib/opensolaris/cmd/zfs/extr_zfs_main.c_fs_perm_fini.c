#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  who_perm_t ;
struct TYPE_9__ {int /*<<< orphan*/  who_perm; } ;
typedef  TYPE_1__ who_perm_node_t ;
struct TYPE_10__ {int /*<<< orphan*/  fsp_uge_avl; int /*<<< orphan*/  fsp_sc_avl; } ;
typedef  TYPE_2__ fs_perm_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  uu_avl_destroy (int /*<<< orphan*/ ) ; 
 TYPE_1__* uu_avl_first (int /*<<< orphan*/ ) ; 
 TYPE_1__* uu_avl_next (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  uu_avl_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  who_perm_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
fs_perm_fini(fs_perm_t *fsperm)
{
	who_perm_node_t *node = uu_avl_first(fsperm->fsp_sc_avl);
	while (node != NULL) {
		who_perm_node_t *next_node = uu_avl_next(fsperm->fsp_sc_avl,
		    node);
		who_perm_t *who_perm = &node->who_perm;
		who_perm_fini(who_perm);
		uu_avl_remove(fsperm->fsp_sc_avl, node);
		free(node);
		node = next_node;
	}

	node = uu_avl_first(fsperm->fsp_uge_avl);
	while (node != NULL) {
		who_perm_node_t *next_node = uu_avl_next(fsperm->fsp_uge_avl,
		    node);
		who_perm_t *who_perm = &node->who_perm;
		who_perm_fini(who_perm);
		uu_avl_remove(fsperm->fsp_uge_avl, node);
		free(node);
		node = next_node;
	}

	uu_avl_destroy(fsperm->fsp_sc_avl);
	uu_avl_destroy(fsperm->fsp_uge_avl);
}