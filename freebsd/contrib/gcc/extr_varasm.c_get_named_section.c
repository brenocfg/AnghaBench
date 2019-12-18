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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  section ;
struct TYPE_2__ {unsigned int (* section_type_flags ) (int /*<<< orphan*/ ,char const*,int) ;} ;

/* Variables and functions */
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SECTION_NAME (int /*<<< orphan*/ ) ; 
 char* TREE_STRING_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/ * get_section (char const*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int stub1 (int /*<<< orphan*/ ,char const*,int) ; 
 TYPE_1__ targetm ; 

section *
get_named_section (tree decl, const char *name, int reloc)
{
  unsigned int flags;

  gcc_assert (!decl || DECL_P (decl));
  if (name == NULL)
    name = TREE_STRING_POINTER (DECL_SECTION_NAME (decl));

  flags = targetm.section_type_flags (decl, name, reloc);

  return get_section (name, flags, decl);
}