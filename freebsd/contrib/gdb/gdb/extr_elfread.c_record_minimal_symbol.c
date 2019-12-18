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
struct objfile {int dummy; } ;
struct minimal_symbol {int dummy; } ;
typedef  enum minimal_symbol_type { ____Placeholder_minimal_symbol_type } minimal_symbol_type ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ asection ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  SMASH_TEXT_ADDRESS (int /*<<< orphan*/ ) ; 
 int mst_file_text ; 
 int mst_text ; 
 struct minimal_symbol* prim_record_minimal_symbol_and_info (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,struct objfile*) ; 

__attribute__((used)) static struct minimal_symbol *
record_minimal_symbol (char *name, CORE_ADDR address,
		       enum minimal_symbol_type ms_type,
		       asection *bfd_section, struct objfile *objfile)
{
  if (ms_type == mst_text || ms_type == mst_file_text)
    address = SMASH_TEXT_ADDRESS (address);

  return prim_record_minimal_symbol_and_info
    (name, address, ms_type, NULL, bfd_section->index, bfd_section, objfile);
}