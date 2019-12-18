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

/* Variables and functions */
 scalar_t__ PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_cached_frames () ; 
 int /*<<< orphan*/  get_current_frame () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  select_frame (int /*<<< orphan*/ ) ; 

void
reinit_frame_cache (void)
{
  flush_cached_frames ();

  /* FIXME: The inferior_ptid test is wrong if there is a corefile.  */
  if (PIDGET (inferior_ptid) != 0)
    {
      select_frame (get_current_frame ());
    }
}