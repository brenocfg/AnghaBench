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
struct TYPE_7__ {struct TYPE_7__* die_left; struct TYPE_7__* die_right; struct TYPE_7__* die_parent; struct TYPE_7__* die_child; } ;
typedef  TYPE_1__* Dwarf_P_Die ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
_dwarf_die_link(Dwarf_P_Die die, Dwarf_P_Die parent, Dwarf_P_Die child,
    Dwarf_P_Die left_sibling, Dwarf_P_Die right_sibling)
{
	Dwarf_P_Die last_child;

	assert(die != NULL);

	if (parent) {

		/* Disconnect from old parent. */
		if (die->die_parent) {
			if (die->die_parent != parent) {
				if (die->die_parent->die_child == die)
					die->die_parent->die_child = NULL;
				die->die_parent = NULL;
                     }
		}

		/* Find the last child of this parent. */
		last_child = parent->die_child;
		if (last_child) {
			while (last_child->die_right != NULL)
				last_child = last_child->die_right;
		}

		/* Connect to new parent. */
		die->die_parent = parent;

		/*
		 * Attach this DIE to the end of sibling list. If new
		 * parent doesn't have any child, set this DIE as the
		 * first child.
		 */
		if (last_child) {
			assert(last_child->die_right == NULL);
			last_child->die_right = die;
			die->die_left = last_child;
		} else
			parent->die_child = die;
	}

	if (child) {

		/* Disconnect from old child. */
		if (die->die_child) {
			if (die->die_child != child) {
				die->die_child->die_parent = NULL;
				die->die_child = NULL;
			}
		}

		/* Connect to new child. */
		die->die_child = child;
		child->die_parent = die;
	}

	if (left_sibling) {

		/* Disconnect from old left sibling. */
		if (die->die_left) {
			if (die->die_left != left_sibling) {
				die->die_left->die_right = NULL;
				die->die_left = NULL;
			}
		}

		/* Connect to new right sibling. */
		die->die_left = left_sibling;
		left_sibling->die_right = die;
	}

	if (right_sibling) {

		/* Disconnect from old right sibling. */
		if (die->die_right) {
			if (die->die_right != right_sibling) {
				die->die_right->die_left = NULL;
				die->die_right = NULL;
			}
		}

		/* Connect to new right sibling. */
		die->die_right = right_sibling;
		right_sibling->die_left = die;
	}
}