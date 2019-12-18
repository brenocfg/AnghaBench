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
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRUCT_DOMAIN ; 
 scalar_t__ alloca (int) ; 
 struct symbol* lookup_symbol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct symtab**) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static struct symbol *
lookup_prefix_sym (char **argptr, char *p)
{
  char *p1;
  char *copy;

  /* Extract the class name.  */
  p1 = p;
  while (p != *argptr && p[-1] == ' ')
    --p;
  copy = (char *) alloca (p - *argptr + 1);
  memcpy (copy, *argptr, p - *argptr);
  copy[p - *argptr] = 0;

  /* Discard the class name from the argptr.  */
  p = p1 + (p1[0] == ':' ? 2 : 1);
  while (*p == ' ' || *p == '\t')
    p++;
  *argptr = p;

  /* At this point p1->"::inA::fun", p->"inA::fun" copy->"AAA",
     argptr->"inA::fun" */

  return lookup_symbol (copy, 0, STRUCT_DOMAIN, 0,
			(struct symtab **) NULL);
}