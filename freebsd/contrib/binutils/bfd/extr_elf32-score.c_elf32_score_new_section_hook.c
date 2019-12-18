#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _score_elf_section_data {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {struct _score_elf_section_data* used_by_bfd; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _bfd_elf_new_section_hook (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct _score_elf_section_data* bfd_zalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bfd_boolean
elf32_score_new_section_hook (bfd *abfd, asection *sec)
{
  struct _score_elf_section_data *sdata;
  bfd_size_type amt = sizeof (*sdata);

  sdata = bfd_zalloc (abfd, amt);
  if (sdata == NULL)
    return FALSE;
  sec->used_by_bfd = sdata;

  return _bfd_elf_new_section_hook (abfd, sec);
}