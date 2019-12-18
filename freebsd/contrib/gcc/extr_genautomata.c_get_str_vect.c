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
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  irp ; 
 int n_sep_els (char const*,int,int) ; 
 char* next_sep_el (char const**,int,int) ; 
 scalar_t__ obstack_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_blank (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  obstack_finish (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char **
get_str_vect (const char *str, int *els_num, int sep, int paren_p)
{
  int i;
  char **vect;
  const char **pstr;
  char *trail;

  *els_num = n_sep_els (str, sep, paren_p);
  if (*els_num <= 0)
    return NULL;
  obstack_blank (&irp, sizeof (char *) * (*els_num + 1));
  vect = (char **) obstack_base (&irp);
  (void) obstack_finish (&irp);
  pstr = &str;
  for (i = 0; i < *els_num; i++)
    vect [i] = next_sep_el (pstr, sep, paren_p);
  trail = next_sep_el (pstr, sep, paren_p);
  gcc_assert (!trail);
  vect [i] = NULL;
  return vect;
}