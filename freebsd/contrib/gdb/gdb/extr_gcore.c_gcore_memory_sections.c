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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcore_copy_callback ; 
 int /*<<< orphan*/  gcore_create_callback ; 
 int /*<<< orphan*/  make_output_phdrs ; 
 scalar_t__ target_find_memory_regions (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
gcore_memory_sections (bfd *obfd)
{
  if (target_find_memory_regions (gcore_create_callback, obfd) != 0)
    return 0;			/* FIXME: error return/msg?  */

  /* Record phdrs for section-to-segment mapping.  */
  bfd_map_over_sections (obfd, make_output_phdrs, NULL);

  /* Copy memory region contents.  */
  bfd_map_over_sections (obfd, gcore_copy_callback, NULL);

  return 1;
}