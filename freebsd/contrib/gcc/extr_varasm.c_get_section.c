#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct named_section {int dummy; } ;
struct TYPE_7__ {unsigned int flags; } ;
struct TYPE_9__ {scalar_t__ decl; int /*<<< orphan*/  name; TYPE_1__ common; } ;
struct TYPE_8__ {unsigned int flags; } ;
struct TYPE_10__ {TYPE_3__ named; TYPE_2__ common; } ;
typedef  TYPE_4__ section ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 unsigned int SECTION_DECLARED ; 
 unsigned int SECTION_NAMED ; 
 unsigned int SECTION_OVERRIDE ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 TYPE_4__* ggc_alloc (int) ; 
 int /*<<< orphan*/  ggc_strdup (char const*) ; 
 scalar_t__ htab_find_slot_with_hash (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_string (char const*) ; 
 int /*<<< orphan*/  section_htab ; 

section *
get_section (const char *name, unsigned int flags, tree decl)
{
  section *sect, **slot;

  slot = (section **)
    htab_find_slot_with_hash (section_htab, name,
			      htab_hash_string (name), INSERT);
  flags |= SECTION_NAMED;
  if (*slot == NULL)
    {
      sect = ggc_alloc (sizeof (struct named_section));
      sect->named.common.flags = flags;
      sect->named.name = ggc_strdup (name);
      sect->named.decl = decl;
      *slot = sect;
    }
  else
    {
      sect = *slot;
      if ((sect->common.flags & ~SECTION_DECLARED) != flags
	  && ((sect->common.flags | flags) & SECTION_OVERRIDE) == 0)
	{
	  /* Sanity check user variables for flag changes.  */
	  if (decl == 0)
	    decl = sect->named.decl;
	  gcc_assert (decl);
	  error ("%+D causes a section type conflict", decl);
	}
    }
  return sect;
}