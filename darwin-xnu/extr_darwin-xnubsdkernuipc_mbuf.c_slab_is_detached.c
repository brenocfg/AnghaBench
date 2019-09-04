#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tqe_prev; scalar_t__ tqe_next; } ;
struct TYPE_5__ {int sl_flags; TYPE_1__ sl_link; } ;
typedef  TYPE_2__ mcl_slab_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int SLF_DETACHED ; 

__attribute__((used)) static boolean_t
slab_is_detached(mcl_slab_t *sp)
{
	return ((intptr_t)sp->sl_link.tqe_next == -1 &&
	    (intptr_t)sp->sl_link.tqe_prev == -1 &&
	    (sp->sl_flags & SLF_DETACHED));
}