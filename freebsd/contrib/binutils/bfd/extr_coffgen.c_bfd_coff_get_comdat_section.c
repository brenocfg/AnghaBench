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
struct coff_comdat_info {int dummy; } ;
struct bfd_section {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {struct coff_comdat_info* comdat; } ;

/* Variables and functions */
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_coff_flavour ; 
 TYPE_1__* coff_section_data (int /*<<< orphan*/ *,struct bfd_section*) ; 

struct coff_comdat_info *
bfd_coff_get_comdat_section (bfd *abfd, struct bfd_section *sec)
{
  if (bfd_get_flavour (abfd) == bfd_target_coff_flavour
      && coff_section_data (abfd, sec) != NULL)
    return coff_section_data (abfd, sec)->comdat;
  else
    return NULL;
}