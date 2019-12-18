#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  asection ;
struct TYPE_3__ {void* opd_adjust; } ;
struct TYPE_4__ {scalar_t__ sec_type; TYPE_1__ u; } ;

/* Variables and functions */
 TYPE_2__* ppc64_elf_section_data (int /*<<< orphan*/ *) ; 
 scalar_t__ sec_opd ; 

__attribute__((used)) static void *
get_opd_info (asection * sec)
{
  if (sec != NULL
      && ppc64_elf_section_data (sec) != NULL
      && ppc64_elf_section_data (sec)->sec_type == sec_opd)
    return ppc64_elf_section_data (sec)->u.opd_adjust;
  return NULL;
}