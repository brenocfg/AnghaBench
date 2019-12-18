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
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_aout_flavour ; 
 scalar_t__ bfd_target_coff_flavour ; 
 scalar_t__ bfd_target_ieee_flavour ; 
 void* debug_init () ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_coff (int /*<<< orphan*/ *,int /*<<< orphan*/ **,long,void*) ; 
 int /*<<< orphan*/  read_ieee_debugging_info (int /*<<< orphan*/ *,void*,scalar_t__*) ; 
 int /*<<< orphan*/  read_section_stabs_debugging_info (int /*<<< orphan*/ *,int /*<<< orphan*/ **,long,void*,scalar_t__*) ; 
 int /*<<< orphan*/  read_symbol_stabs_debugging_info (int /*<<< orphan*/ *,int /*<<< orphan*/ **,long,void*,scalar_t__*) ; 

void *
read_debugging_info (bfd *abfd, asymbol **syms, long symcount)
{
  void *dhandle;
  bfd_boolean found;

  dhandle = debug_init ();
  if (dhandle == NULL)
    return NULL;

  if (! read_section_stabs_debugging_info (abfd, syms, symcount, dhandle,
					   &found))
    return NULL;

  if (bfd_get_flavour (abfd) == bfd_target_aout_flavour)
    {
      if (! read_symbol_stabs_debugging_info (abfd, syms, symcount, dhandle,
					      &found))
	return NULL;
    }

  if (bfd_get_flavour (abfd) == bfd_target_ieee_flavour)
    {
      if (! read_ieee_debugging_info (abfd, dhandle, &found))
	return NULL;
    }

  /* Try reading the COFF symbols if we didn't find any stabs in COFF
     sections.  */
  if (! found
      && bfd_get_flavour (abfd) == bfd_target_coff_flavour
      && symcount > 0)
    {
      if (! parse_coff (abfd, syms, symcount, dhandle))
	return NULL;
      found = TRUE;
    }

  if (! found)
    {
      non_fatal (_("%s: no recognized debugging information"),
		 bfd_get_filename (abfd));
      return NULL;
    }

  return dhandle;
}