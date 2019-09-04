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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {TYPE_1__* lck_mtx_ptr; } ;
typedef  TYPE_2__ lck_mtx_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {TYPE_2__ lck_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ordered_load_mtx_state (TYPE_2__*) ; 

__attribute__((used)) __attribute__((always_inline))
static boolean_t
get_indirect_mutex(
	lck_mtx_t       **lock,
	uint32_t	*state)
{
	*lock = &((*lock)->lck_mtx_ptr->lck_mtx);
	*state = ordered_load_mtx_state(*lock);
	return TRUE;
}