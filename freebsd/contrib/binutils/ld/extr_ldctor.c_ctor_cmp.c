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
struct set_element {char* name; } ;

/* Variables and functions */
 int ctor_prio (char const*) ; 

__attribute__((used)) static int
ctor_cmp (const void *p1, const void *p2)
{
  const struct set_element * const *pe1 = p1;
  const struct set_element * const *pe2 = p2;
  const char *n1;
  const char *n2;
  int prio1;
  int prio2;

  n1 = (*pe1)->name;
  if (n1 == NULL)
    n1 = "";
  n2 = (*pe2)->name;
  if (n2 == NULL)
    n2 = "";

  /* We need to sort in reverse order by priority.  When two
     constructors have the same priority, we should maintain their
     current relative position.  */

  prio1 = ctor_prio (n1);
  prio2 = ctor_prio (n2);

  /* We sort in reverse order because that is what g++ expects.  */
  if (prio1 < prio2)
    return 1;
  else if (prio1 > prio2)
    return -1;

  /* Force a stable sort.  */

  if (pe1 < pe2)
    return -1;
  else if (pe1 > pe2)
    return 1;
  else
    return 0;
}