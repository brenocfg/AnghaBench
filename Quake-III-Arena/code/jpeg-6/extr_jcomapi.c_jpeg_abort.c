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
typedef  TYPE_2__* j_common_ptr ;
struct TYPE_6__ {scalar_t__ is_decompressor; int /*<<< orphan*/  global_state; TYPE_1__* mem; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* free_pool ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CSTATE_START ; 
 int /*<<< orphan*/  DSTATE_START ; 
 int JPOOL_NUMPOOLS ; 
 int JPOOL_PERMANENT ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

void
jpeg_abort (j_common_ptr cinfo)
{
  int pool;

  /* Releasing pools in reverse order might help avoid fragmentation
   * with some (brain-damaged) malloc libraries.
   */
  for (pool = JPOOL_NUMPOOLS-1; pool > JPOOL_PERMANENT; pool--) {
    (*cinfo->mem->free_pool) (cinfo, pool);
  }

  /* Reset overall state for possible reuse of object */
  cinfo->global_state = (cinfo->is_decompressor ? DSTATE_START : CSTATE_START);
}