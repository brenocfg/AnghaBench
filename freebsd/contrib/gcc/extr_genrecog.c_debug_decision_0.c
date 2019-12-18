#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct decision* first; } ;
struct decision {struct decision* next; TYPE_1__ success; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_decision_1 (struct decision*,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
debug_decision_0 (struct decision *d, int indent, int maxdepth)
{
  struct decision *n;
  int i;

  if (maxdepth < 0)
    return;
  if (d == NULL)
    {
      for (i = 0; i < indent; ++i)
	putc (' ', stderr);
      fputs ("(nil)\n", stderr);
      return;
    }

  debug_decision_1 (d, indent);
  for (n = d->success.first; n ; n = n->next)
    debug_decision_0 (n, indent + 2, maxdepth - 1);
}