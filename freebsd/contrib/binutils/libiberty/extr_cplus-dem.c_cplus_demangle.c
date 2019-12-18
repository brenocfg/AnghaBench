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
typedef  int /*<<< orphan*/  work ;
struct work_stuff {int options; } ;

/* Variables and functions */
 scalar_t__ AUTO_DEMANGLING ; 
 int DMGL_STYLE_MASK ; 
 scalar_t__ GNAT_DEMANGLING ; 
 scalar_t__ GNU_V3_DEMANGLING ; 
 scalar_t__ JAVA_DEMANGLING ; 
 char* ada_demangle (char const*,int) ; 
 char* cplus_demangle_v3 (char const*,int) ; 
 scalar_t__ current_demangling_style ; 
 char* internal_cplus_demangle (struct work_stuff*,char const*) ; 
 char* java_demangle_v3 (char const*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ no_demangling ; 
 int /*<<< orphan*/  squangle_mop_up (struct work_stuff*) ; 
 char* xstrdup (char const*) ; 

char *
cplus_demangle (const char *mangled, int options)
{
  char *ret;
  struct work_stuff work[1];

  if (current_demangling_style == no_demangling)
    return xstrdup (mangled);

  memset ((char *) work, 0, sizeof (work));
  work->options = options;
  if ((work->options & DMGL_STYLE_MASK) == 0)
    work->options |= (int) current_demangling_style & DMGL_STYLE_MASK;

  /* The V3 ABI demangling is implemented elsewhere.  */
  if (GNU_V3_DEMANGLING || AUTO_DEMANGLING)
    {
      ret = cplus_demangle_v3 (mangled, work->options);
      if (ret || GNU_V3_DEMANGLING)
	return ret;
    }

  if (JAVA_DEMANGLING)
    {
      ret = java_demangle_v3 (mangled);
      if (ret)
        return ret;
    }

  if (GNAT_DEMANGLING)
    return ada_demangle(mangled,options);

  ret = internal_cplus_demangle (work, mangled);
  squangle_mop_up (work);
  return (ret);
}