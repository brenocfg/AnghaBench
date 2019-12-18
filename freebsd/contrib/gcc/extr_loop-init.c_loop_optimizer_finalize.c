#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct loops {unsigned int num; scalar_t__* parray; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_loops_free (struct loops*) ; 
 int /*<<< orphan*/  free (struct loops*) ; 
 int /*<<< orphan*/  free_simple_loop_desc (scalar_t__) ; 
 int /*<<< orphan*/  verify_flow_info () ; 

void
loop_optimizer_finalize (struct loops *loops)
{
  unsigned i;

  if (!loops)
    return;

  for (i = 1; i < loops->num; i++)
    if (loops->parray[i])
      free_simple_loop_desc (loops->parray[i]);

  /* Clean up.  */
  flow_loops_free (loops);
  free (loops);

  /* Checking.  */
#ifdef ENABLE_CHECKING
  verify_flow_info ();
#endif
}