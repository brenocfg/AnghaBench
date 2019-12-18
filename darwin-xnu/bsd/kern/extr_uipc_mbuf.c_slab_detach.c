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
struct TYPE_4__ {TYPE_2__** tqe_prev; TYPE_2__* tqe_next; } ;
struct TYPE_5__ {int /*<<< orphan*/  sl_flags; TYPE_1__ sl_link; } ;
typedef  TYPE_2__ mcl_slab_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLF_DETACHED ; 

__attribute__((used)) static void
slab_detach(mcl_slab_t *sp)
{
	sp->sl_link.tqe_next = (mcl_slab_t *)-1;
	sp->sl_link.tqe_prev = (mcl_slab_t **)-1;
	sp->sl_flags |= SLF_DETACHED;
}