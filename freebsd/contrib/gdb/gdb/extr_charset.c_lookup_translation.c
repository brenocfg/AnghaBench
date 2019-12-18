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
struct translation {int /*<<< orphan*/  to; int /*<<< orphan*/  from; struct translation* next; } ;

/* Variables and functions */
 struct translation* all_translations ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct translation *
lookup_translation (const char *from, const char *to)
{
  struct translation *t;

  for (t = all_translations; t; t = t->next)
    if (! strcmp (from, t->from)
        && ! strcmp (to, t->to))
      return t;

  return 0;
}