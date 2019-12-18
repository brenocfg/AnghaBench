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
struct TYPE_3__ {scalar_t__ text_base; scalar_t__ text_size; } ;
struct TYPE_4__ {TYPE_1__ dld_desc; int /*<<< orphan*/  have_read_dld_descriptor; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  auto_solib_add ; 
 int /*<<< orphan*/  current_target ; 
 TYPE_2__ dld_cache ; 
 int /*<<< orphan*/  read_dld_descriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * symfile_objfile ; 

int
pa64_solib_in_dynamic_linker (int pid, CORE_ADDR pc)
{
  asection *shlib_info;

  if (symfile_objfile == NULL)
    return 0;

  if (!dld_cache.have_read_dld_descriptor)
    if (!read_dld_descriptor (&current_target, auto_solib_add))
      return 0;

  return (pc >= dld_cache.dld_desc.text_base
	  && pc < dld_cache.dld_desc.text_base + dld_cache.dld_desc.text_size);
}