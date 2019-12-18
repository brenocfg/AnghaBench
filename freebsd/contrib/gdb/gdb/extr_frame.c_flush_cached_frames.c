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
 int /*<<< orphan*/  annotate_frames_invalid () ; 
 int /*<<< orphan*/ * current_frame ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  frame_cache_obstack ; 
 scalar_t__ frame_debug ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  select_frame (int /*<<< orphan*/ *) ; 

void
flush_cached_frames (void)
{
  /* Since we can't really be sure what the first object allocated was */
  obstack_free (&frame_cache_obstack, 0);
  obstack_init (&frame_cache_obstack);

  current_frame = NULL;		/* Invalidate cache */
  select_frame (NULL);
  annotate_frames_invalid ();
  if (frame_debug)
    fprintf_unfiltered (gdb_stdlog, "{ flush_cached_frames () }\n");
}