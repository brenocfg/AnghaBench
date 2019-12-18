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
typedef  int /*<<< orphan*/  lang_memory_region_type ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MEMORY_REGION ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lang_memory_region_lookup (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lang_get_regions (lang_memory_region_type **region,
		  lang_memory_region_type **lma_region,
		  const char *memspec,
		  const char *lma_memspec,
		  bfd_boolean have_lma,
		  bfd_boolean have_vma)
{
  *lma_region = lang_memory_region_lookup (lma_memspec, FALSE);

  /* If no runtime region or VMA has been specified, but the load region
     has been specified, then use the load region for the runtime region
     as well.  */
  if (lma_memspec != NULL
      && ! have_vma
      && strcmp (memspec, DEFAULT_MEMORY_REGION) == 0)
    *region = *lma_region;
  else
    *region = lang_memory_region_lookup (memspec, FALSE);

  if (have_lma && lma_memspec != 0)
    einfo (_("%X%P:%S: section has both a load address and a load region\n"));
}