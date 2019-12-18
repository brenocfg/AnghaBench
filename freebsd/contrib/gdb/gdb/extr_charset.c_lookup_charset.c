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
struct charset {int /*<<< orphan*/  name; struct charset* next; } ;

/* Variables and functions */
 struct charset* all_charsets ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct charset *
lookup_charset (const char *name)
{
  struct charset *cs;

  for (cs = all_charsets; cs; cs = cs->next)
    if (! strcmp (name, cs->name))
      return cs;

  return NULL;
}