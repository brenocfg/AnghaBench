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
struct stab_demangle_typestring {char const* typestring; unsigned int len; } ;
struct stab_demangle_info {int typestring_count; int typestring_alloc; struct stab_demangle_typestring* typestrings; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ xrealloc (struct stab_demangle_typestring*,int) ; 

__attribute__((used)) static bfd_boolean
stab_demangle_remember_type (struct stab_demangle_info *minfo,
			     const char *p, int len)
{
  if (minfo->typestring_count >= minfo->typestring_alloc)
    {
      minfo->typestring_alloc += 10;
      minfo->typestrings = ((struct stab_demangle_typestring *)
			    xrealloc (minfo->typestrings,
				      (minfo->typestring_alloc
				       * sizeof *minfo->typestrings)));
    }

  minfo->typestrings[minfo->typestring_count].typestring = p;
  minfo->typestrings[minfo->typestring_count].len = (unsigned int) len;
  ++minfo->typestring_count;

  return TRUE;
}