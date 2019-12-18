#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int /*<<< orphan*/ * notice_hash; int /*<<< orphan*/  notice_all; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_2__ {scalar_t__ cref; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_cref (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_hash_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_is_und_section (int /*<<< orphan*/ *) ; 
 TYPE_1__ command_line ; 
 int /*<<< orphan*/  einfo (char*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  handle_asneeded_cref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nocrossref_list ; 

__attribute__((used)) static bfd_boolean
notice (struct bfd_link_info *info,
	const char *name,
	bfd *abfd,
	asection *section,
	bfd_vma value)
{
  if (name == NULL)
    {
      if (command_line.cref || nocrossref_list != NULL)
	return handle_asneeded_cref (abfd, value);
      return TRUE;
    }

  if (! info->notice_all
      || (info->notice_hash != NULL
	  && bfd_hash_lookup (info->notice_hash, name, FALSE, FALSE) != NULL))
    {
      if (bfd_is_und_section (section))
	einfo ("%B: reference to %s\n", abfd, name);
      else
	einfo ("%B: definition of %s\n", abfd, name);
    }

  if (command_line.cref || nocrossref_list != NULL)
    add_cref (name, abfd, section, value);

  return TRUE;
}