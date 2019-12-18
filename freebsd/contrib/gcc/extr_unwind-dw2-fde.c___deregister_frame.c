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
typedef  scalar_t__ uword ;

/* Variables and functions */
 int /*<<< orphan*/  __deregister_frame_info (void*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void
__deregister_frame (void *begin)
{
  /* If .eh_frame is empty, we haven't registered.  */
  if (*(uword *) begin != 0)
    free (__deregister_frame_info (begin));
}