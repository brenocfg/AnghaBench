#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct elfcopy {int flags; int /*<<< orphan*/  v_grp; int /*<<< orphan*/  v_rel; } ;
struct TYPE_3__ {int /*<<< orphan*/  st_info; } ;
typedef  TYPE_1__ GElf_Sym ;

/* Variables and functions */
 scalar_t__ BIT_ISSET (int /*<<< orphan*/ ,int) ; 
 int RELOCATABLE ; 
 scalar_t__ is_global_symbol (int /*<<< orphan*/ ) ; 
 scalar_t__ is_weak_symbol (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_needed_symbol(struct elfcopy *ecp, int i, GElf_Sym *s)
{

	/* If symbol involves relocation, it is needed. */
	if (BIT_ISSET(ecp->v_rel, i))
		return (1);

	/* Symbols referred by COMDAT sections are needed. */
	if (BIT_ISSET(ecp->v_grp, i))
		return (1);

	/*
	 * For relocatable files (.o files), global and weak symbols
	 * are needed.
	 */
	if (ecp->flags & RELOCATABLE) {
		if (is_global_symbol(s->st_info) || is_weak_symbol(s->st_info))
			return (1);
	}

	return (0);
}