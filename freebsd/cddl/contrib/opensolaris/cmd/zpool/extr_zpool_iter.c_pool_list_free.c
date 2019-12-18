#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zl_pool; int /*<<< orphan*/  zl_avl; int /*<<< orphan*/  zn_handle; } ;
typedef  TYPE_1__ zpool_node_t ;
typedef  TYPE_1__ zpool_list_t ;
typedef  int /*<<< orphan*/  uu_avl_walk_t ;

/* Variables and functions */
 int /*<<< orphan*/  UU_WALK_ROBUST ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uu_avl_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_avl_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_avl_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  uu_avl_walk_end (int /*<<< orphan*/ *) ; 
 TYPE_1__* uu_avl_walk_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uu_avl_walk_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ ) ; 

void
pool_list_free(zpool_list_t *zlp)
{
	uu_avl_walk_t *walk;
	zpool_node_t *node;

	if ((walk = uu_avl_walk_start(zlp->zl_avl, UU_WALK_ROBUST)) == NULL) {
		(void) fprintf(stderr,
		    gettext("internal error: out of memory"));
		exit(1);
	}

	while ((node = uu_avl_walk_next(walk)) != NULL) {
		uu_avl_remove(zlp->zl_avl, node);
		zpool_close(node->zn_handle);
		free(node);
	}

	uu_avl_walk_end(walk);
	uu_avl_destroy(zlp->zl_avl);
	uu_avl_pool_destroy(zlp->zl_pool);

	free(zlp);
}