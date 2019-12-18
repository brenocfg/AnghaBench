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
struct dummy_frame {int /*<<< orphan*/  regcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  discard_innermost_dummy (struct dummy_frame**) ; 
 struct dummy_frame* dummy_frame_stack ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  flush_cached_frames () ; 
 int /*<<< orphan*/  regcache_cpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
generic_pop_dummy_frame (void)
{
  struct dummy_frame *dummy_frame = dummy_frame_stack;

  /* FIXME: what if the first frame isn't the right one, eg..
     because one call-by-hand function has done a longjmp into another one? */

  if (!dummy_frame)
    error ("Can't pop dummy frame!");
  regcache_cpy (current_regcache, dummy_frame->regcache);
  flush_cached_frames ();

  discard_innermost_dummy (&dummy_frame_stack);
}