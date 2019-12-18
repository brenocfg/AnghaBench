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
struct deps {scalar_t__ ntargets; } ;

/* Variables and functions */
 char const* TARGET_OBJECT_SUFFIX ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  deps_add_target (struct deps*,char*,int) ; 
 char* lbasename (char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* strrchr (char*,char) ; 

void
deps_add_default_target (struct deps *d, const char *tgt)
{
  /* Only if we have no targets.  */
  if (d->ntargets)
    return;

  if (tgt[0] == '\0')
    deps_add_target (d, "-", 1);
  else
    {
#ifndef TARGET_OBJECT_SUFFIX
# define TARGET_OBJECT_SUFFIX ".o"
#endif
      const char *start = lbasename (tgt);
      char *o = (char *) alloca (strlen (start)
                                 + strlen (TARGET_OBJECT_SUFFIX) + 1);
      char *suffix;

      strcpy (o, start);

      suffix = strrchr (o, '.');
      if (!suffix)
        suffix = o + strlen (o);
      strcpy (suffix, TARGET_OBJECT_SUFFIX);

      deps_add_target (d, o, 1);
    }
}