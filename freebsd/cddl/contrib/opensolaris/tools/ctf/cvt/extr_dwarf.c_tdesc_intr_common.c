#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t t_size; int t_id; int /*<<< orphan*/  t_flags; TYPE_2__* t_intr; int /*<<< orphan*/  t_type; int /*<<< orphan*/  t_name; } ;
typedef  TYPE_1__ tdesc_t ;
struct TYPE_6__ {int intr_signed; size_t intr_nbits; int /*<<< orphan*/  intr_type; } ;
typedef  TYPE_2__ intr_t ;
typedef  int /*<<< orphan*/  dwarf_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTRINSIC ; 
 int /*<<< orphan*/  INTR_INT ; 
 size_t NBBY ; 
 int /*<<< orphan*/  TDESC_F_RESOLVED ; 
 int /*<<< orphan*/  tdesc_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* xcalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static tdesc_t *
tdesc_intr_common(dwarf_t *dw, int tid, const char *name, size_t sz)
{
	tdesc_t *tdp;
	intr_t *intr;

	intr = xcalloc(sizeof (intr_t));
	intr->intr_type = INTR_INT;
	intr->intr_signed = 1;
	intr->intr_nbits = sz * NBBY;

	tdp = xcalloc(sizeof (tdesc_t));
	tdp->t_name = xstrdup(name);
	tdp->t_size = sz;
	tdp->t_id = tid;
	tdp->t_type = INTRINSIC;
	tdp->t_intr = intr;
	tdp->t_flags = TDESC_F_RESOLVED;

	tdesc_add(dw, tdp);

	return (tdp);
}