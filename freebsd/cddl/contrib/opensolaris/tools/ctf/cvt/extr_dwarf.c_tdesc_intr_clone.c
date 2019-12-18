#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int t_flags; TYPE_5__* t_intr; int /*<<< orphan*/  t_type; int /*<<< orphan*/  t_id; int /*<<< orphan*/  t_size; int /*<<< orphan*/  t_name; } ;
typedef  TYPE_1__ tdesc_t ;
typedef  int /*<<< orphan*/  intr_t ;
typedef  int /*<<< orphan*/  dwarf_t ;
struct TYPE_8__ {size_t intr_nbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTRINSIC ; 
 int TDESC_F_RESOLVED ; 
 int /*<<< orphan*/  bcopy (TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  mfgtid_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdesc_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  terminate (char*,int /*<<< orphan*/ ) ; 
 void* xcalloc (int) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tdesc_t *
tdesc_intr_clone(dwarf_t *dw, tdesc_t *old, size_t bitsz)
{
	tdesc_t *new = xcalloc(sizeof (tdesc_t));

	if (!(old->t_flags & TDESC_F_RESOLVED)) {
		terminate("tdp %u: attempt to make a bit field from an "
		    "unresolved type\n", old->t_id);
	}

	new->t_name = xstrdup(old->t_name);
	new->t_size = old->t_size;
	new->t_id = mfgtid_next(dw);
	new->t_type = INTRINSIC;
	new->t_flags = TDESC_F_RESOLVED;

	new->t_intr = xcalloc(sizeof (intr_t));
	bcopy(old->t_intr, new->t_intr, sizeof (intr_t));
	new->t_intr->intr_nbits = bitsz;

	tdesc_add(dw, new);

	return (new);
}