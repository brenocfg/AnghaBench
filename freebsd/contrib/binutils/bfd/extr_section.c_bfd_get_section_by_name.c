#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct section_hash_entry {int /*<<< orphan*/  section; } ;
struct TYPE_3__ {int /*<<< orphan*/  section_htab; } ;
typedef  TYPE_1__ bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 struct section_hash_entry* section_hash_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

asection *
bfd_get_section_by_name (bfd *abfd, const char *name)
{
  struct section_hash_entry *sh;

  sh = section_hash_lookup (&abfd->section_htab, name, FALSE, FALSE);
  if (sh != NULL)
    return &sh->section;

  return NULL;
}