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
typedef  int /*<<< orphan*/  symbolS ;

/* Variables and functions */
 char* GP_DISP_LABEL ; 
 char* S_GET_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_VALUE (int /*<<< orphan*/ *) ; 
 scalar_t__ S_IS_COMMON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IS_DEFINED (int /*<<< orphan*/ *) ; 
 scalar_t__ USE_GLOBAL_POINTER_OPT ; 
 scalar_t__ g_switch_value ; 
 char* segment_name (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int
nopic_need_relax (symbolS * sym, int before_relaxing)
{
  if (sym == NULL)
    return 0;
  else if (USE_GLOBAL_POINTER_OPT && g_switch_value > 0)
    {
      const char *symname;
      const char *segname;

      /* Find out whether this symbol can be referenced off the $gp
         register.  It can be if it is smaller than the -G size or if
         it is in the .sdata or .sbss section.  Certain symbols can
         not be referenced off the $gp, although it appears as though
         they can.  */
      symname = S_GET_NAME (sym);
      if (symname != (const char *)NULL
          && (strcmp (symname, "eprol") == 0
              || strcmp (symname, "etext") == 0
              || strcmp (symname, "_gp") == 0
              || strcmp (symname, "edata") == 0
              || strcmp (symname, "_fbss") == 0
              || strcmp (symname, "_fdata") == 0
              || strcmp (symname, "_ftext") == 0
              || strcmp (symname, "end") == 0
              || strcmp (symname, GP_DISP_LABEL) == 0))
        {
          return 1;
        }
      else if ((!S_IS_DEFINED (sym) || S_IS_COMMON (sym)) && (0
      /* We must defer this decision until after the whole file has been read,
         since there might be a .extern after the first use of this symbol.  */
               || (before_relaxing
                   && S_GET_VALUE (sym) == 0)
               || (S_GET_VALUE (sym) != 0
                   && S_GET_VALUE (sym) <= g_switch_value)))
        {
          return 0;
        }

      segname = segment_name (S_GET_SEGMENT (sym));
      return (strcmp (segname, ".sdata") != 0
	      && strcmp (segname, ".sbss") != 0
	      && strncmp (segname, ".sdata.", 7) != 0
	      && strncmp (segname, ".gnu.linkonce.s.", 16) != 0);
    }
  /* We are not optimizing for the $gp register.  */
  else
    return 1;
}