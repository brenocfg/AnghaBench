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
 int ISDIGIT (char const) ; 
 int /*<<< orphan*/  builtin_define_with_value_n (char*,char const*,int) ; 
 scalar_t__ c_dialect_cxx () ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 char const* version_string ; 

__attribute__((used)) static void
define__GNUC__ (void)
{
  /* The format of the version string, enforced below, is
     ([^0-9]*-)?[0-9]+[.][0-9]+([.][0-9]+)?([- ].*)?  */
  const char *q, *v = version_string;

  while (*v && !ISDIGIT (*v))
    v++;
  gcc_assert (*v && (v <= version_string || v[-1] == '-'));

  q = v;
  while (ISDIGIT (*v))
    v++;
  builtin_define_with_value_n ("__GNUC__", q, v - q);
  if (c_dialect_cxx ())
    builtin_define_with_value_n ("__GNUG__", q, v - q);

  gcc_assert (*v == '.' && ISDIGIT (v[1]));

  q = ++v;
  while (ISDIGIT (*v))
    v++;
  builtin_define_with_value_n ("__GNUC_MINOR__", q, v - q);

  if (*v == '.')
    {
      gcc_assert (ISDIGIT (v[1]));
      q = ++v;
      while (ISDIGIT (*v))
	v++;
      builtin_define_with_value_n ("__GNUC_PATCHLEVEL__", q, v - q);
    }
  else
    builtin_define_with_value_n ("__GNUC_PATCHLEVEL__", "0", 1);

  gcc_assert (!*v || *v == ' ' || *v == '-');
}