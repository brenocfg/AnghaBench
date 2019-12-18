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
struct core_fns {scalar_t__ (* core_sniffer ) (struct core_fns*,int /*<<< orphan*/ *) ;struct core_fns* next; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 struct core_fns* core_file_fns ; 
 scalar_t__ core_gdbarch ; 
 scalar_t__ gdbarch_regset_from_core_section_p (scalar_t__) ; 
 scalar_t__ stub1 (struct core_fns*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static struct core_fns *
sniff_core_bfd (bfd *abfd)
{
  struct core_fns *cf;
  struct core_fns *yummy = NULL;
  int matches = 0;;

  /* Don't sniff if we have support for register sets in CORE_GDBARCH.  */
  if (core_gdbarch && gdbarch_regset_from_core_section_p (core_gdbarch))
    return NULL;

  for (cf = core_file_fns; cf != NULL; cf = cf->next)
    {
      if (cf->core_sniffer (cf, abfd))
	{
	  yummy = cf;
	  matches++;
	}
    }
  if (matches > 1)
    {
      warning ("\"%s\": ambiguous core format, %d handlers match",
	       bfd_get_filename (abfd), matches);
    }
  else if (matches == 0)
    {
      warning ("\"%s\": no core file handler recognizes format, using default",
	       bfd_get_filename (abfd));
    }
  if (yummy == NULL)
    {
      yummy = core_file_fns;
    }
  return (yummy);
}