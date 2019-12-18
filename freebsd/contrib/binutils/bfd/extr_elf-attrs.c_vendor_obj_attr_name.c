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
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {char const* obj_attrs_vendor; } ;

/* Variables and functions */
 int OBJ_ATTR_PROC ; 
 TYPE_1__* get_elf_backend_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
vendor_obj_attr_name (bfd *abfd, int vendor)
{
  return (vendor == OBJ_ATTR_PROC
	  ? get_elf_backend_data (abfd)->obj_attrs_vendor
	  : "gnu");
}