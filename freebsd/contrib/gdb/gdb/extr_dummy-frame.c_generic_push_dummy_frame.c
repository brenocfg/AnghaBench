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
struct dummy_frame {struct dummy_frame* next; int /*<<< orphan*/  regcache; int /*<<< orphan*/  id; int /*<<< orphan*/  fp; scalar_t__ top; int /*<<< orphan*/  sp; int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ INNER_THAN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  current_regcache ; 
 struct dummy_frame* dummy_frame_stack ; 
 int /*<<< orphan*/  get_current_frame () ; 
 int /*<<< orphan*/  get_frame_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_frame_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_pc () ; 
 int /*<<< orphan*/  read_sp () ; 
 int /*<<< orphan*/  regcache_cpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_xfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_xmalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct dummy_frame*) ; 
 struct dummy_frame* xmalloc (int) ; 

void
generic_push_dummy_frame (void)
{
  struct dummy_frame *dummy_frame;
  CORE_ADDR fp = get_frame_base (get_current_frame ());

  /* check to see if there are stale dummy frames, 
     perhaps left over from when a longjump took us out of a 
     function that was called by the debugger */

  dummy_frame = dummy_frame_stack;
  while (dummy_frame)
    if (INNER_THAN (dummy_frame->fp, fp))	/* stale -- destroy! */
      {
	dummy_frame_stack = dummy_frame->next;
	regcache_xfree (dummy_frame->regcache);
	xfree (dummy_frame);
	dummy_frame = dummy_frame_stack;
      }
    else
      dummy_frame = dummy_frame->next;

  dummy_frame = xmalloc (sizeof (struct dummy_frame));
  dummy_frame->regcache = regcache_xmalloc (current_gdbarch);

  dummy_frame->pc = read_pc ();
  dummy_frame->sp = read_sp ();
  dummy_frame->top = 0;
  dummy_frame->fp = fp;
  dummy_frame->id = get_frame_id (get_current_frame ());
  regcache_cpy (dummy_frame->regcache, current_regcache);
  dummy_frame->next = dummy_frame_stack;
  dummy_frame_stack = dummy_frame;
}