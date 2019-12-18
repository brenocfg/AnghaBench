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
struct change {struct change* link; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_script (struct change*) ; 
 struct change* stub1 (struct change*) ; 
 void stub2 (struct change*) ; 

void
print_script (struct change *script,
	      struct change * (*hunkfun) (struct change *),
	      void (*printfun) (struct change *))
{
  struct change *next = script;

  while (next)
    {
      struct change *this, *end;

      /* Find a set of changes that belong together.  */
      this = next;
      end = (*hunkfun) (next);

      /* Disconnect them from the rest of the changes,
	 making them a hunk, and remember the rest for next iteration.  */
      next = end->link;
      end->link = 0;
#ifdef DEBUG
      debug_script (this);
#endif

      /* Print this hunk.  */
      (*printfun) (this);

      /* Reconnect the script so it will all be freed properly.  */
      end->link = next;
    }
}