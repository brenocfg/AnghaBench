#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* name; int /*<<< orphan*/  flags; } ;
struct section_hash_entry {TYPE_2__ section; } ;
typedef  int /*<<< orphan*/  flagword ;
struct TYPE_8__ {int /*<<< orphan*/  section_htab; scalar_t__ output_has_begun; } ;
typedef  TYPE_1__ bfd ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ABS_SECTION_NAME ; 
 int /*<<< orphan*/  BFD_COM_SECTION_NAME ; 
 int /*<<< orphan*/  BFD_IND_SECTION_NAME ; 
 int /*<<< orphan*/  BFD_UND_SECTION_NAME ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 TYPE_2__* bfd_section_init (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 struct section_hash_entry* section_hash_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

asection *
bfd_make_section_with_flags (bfd *abfd, const char *name,
			     flagword flags)
{
  struct section_hash_entry *sh;
  asection *newsect;

  if (abfd->output_has_begun)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return NULL;
    }

  if (strcmp (name, BFD_ABS_SECTION_NAME) == 0
      || strcmp (name, BFD_COM_SECTION_NAME) == 0
      || strcmp (name, BFD_UND_SECTION_NAME) == 0
      || strcmp (name, BFD_IND_SECTION_NAME) == 0)
    return NULL;

  sh = section_hash_lookup (&abfd->section_htab, name, TRUE, FALSE);
  if (sh == NULL)
    return NULL;

  newsect = &sh->section;
  if (newsect->name != NULL)
    {
      /* Section already exists.  */
      return NULL;
    }

  newsect->name = name;
  newsect->flags = flags;
  return bfd_section_init (abfd, newsect);
}