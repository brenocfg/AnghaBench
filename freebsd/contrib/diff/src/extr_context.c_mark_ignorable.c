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
struct change {int ignore; struct change* link; } ;
typedef  int /*<<< orphan*/  lin ;

/* Variables and functions */
 int /*<<< orphan*/  analyze_hunk (struct change*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mark_ignorable (struct change *script)
{
  while (script)
    {
      struct change *next = script->link;
      lin first0, last0, first1, last1;

      /* Turn this change into a hunk: detach it from the others.  */
      script->link = 0;

      /* Determine whether this change is ignorable.  */
      script->ignore = ! analyze_hunk (script,
				       &first0, &last0, &first1, &last1);

      /* Reconnect the chain as before.  */
      script->link = next;

      /* Advance to the following change.  */
      script = next;
    }
}