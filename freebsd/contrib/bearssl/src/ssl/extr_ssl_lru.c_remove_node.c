#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ store; } ;
typedef  TYPE_1__ br_ssl_session_cache_lru ;

/* Variables and functions */
 scalar_t__ ADDR_NULL ; 
 scalar_t__ SESSION_ID_OFF ; 
 int /*<<< orphan*/  find_node (TYPE_1__*,scalar_t__,scalar_t__*) ; 
 scalar_t__ find_replacement_node (TYPE_1__*,scalar_t__,scalar_t__*) ; 
 scalar_t__ get_left (TYPE_1__*,scalar_t__) ; 
 scalar_t__ get_right (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  set_left (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_link (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_right (TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
remove_node(br_ssl_session_cache_lru *cc, uint32_t x)
{
	uint32_t alx, y, aly;

	/*
	 * Removal algorithm:
	 * ------------------
	 *
	 * - If we remove the root, then the tree becomes empty.
	 *
	 * - If the removed node has no child, then we can simply remove
	 *   it, with nothing else to do.
	 *
	 * - Otherwise, the removed node must be replaced by either its
	 *   rightmost left-descendent, or its leftmost right-descendent.
	 *   The replacement node itself must be removed from its current
	 *   place. By definition, that replacement node has either no
	 *   child, or at most a single child that will replace it in the
	 *   tree.
	 */

	/*
	 * Find node back and its ancestor link. If the node was the
	 * root, then alx is set to ADDR_NULL.
	 */
	find_node(cc, cc->store + x + SESSION_ID_OFF, &alx);

	/*
	 * Find replacement node 'y', and 'aly' is set to the address of
	 * the link to that replacement node. If the removed node has no
	 * child, then both 'y' and 'aly' are set to ADDR_NULL.
	 */
	y = find_replacement_node(cc, x, &aly);

	if (y != ADDR_NULL) {
		uint32_t z;

		/*
		 * The unlinked replacement node may have one child (but
		 * not two) that takes its place.
		 */
		z = get_left(cc, y);
		if (z == ADDR_NULL) {
			z = get_right(cc, y);
		}
		set_link(cc, aly, z);

		/*
		 * Link the replacement node in its new place, overwriting
		 * the current link to the node 'x' (which removes 'x').
		 */
		set_link(cc, alx, y);

		/*
		 * The replacement node adopts the left and right children
		 * of the removed node. Note that this also works even if
		 * the replacement node was a direct descendent of the
		 * removed node, since we unlinked it previously.
		 */
		set_left(cc, y, get_left(cc, x));
		set_right(cc, y, get_right(cc, x));
	} else {
		/*
		 * No replacement, we simply unlink the node 'x'.
		 */
		set_link(cc, alx, ADDR_NULL);
	}
}