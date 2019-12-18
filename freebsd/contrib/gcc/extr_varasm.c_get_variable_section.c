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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  section ;
struct TYPE_3__ {int /*<<< orphan*/ * (* select_section ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ asm_out; scalar_t__ have_switchable_bss_sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_COMMON (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_INITIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DECL_SECTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_THREAD_LOCAL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ IN_NAMED_SECTION (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ bss_initializer_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bss_noswitch_section ; 
 int /*<<< orphan*/ * comm_section ; 
 int compute_reloc_for_constant (scalar_t__) ; 
 scalar_t__ contains_pointers_p (int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  flag_data_sections ; 
 int /*<<< orphan*/ * get_named_section (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lcomm_section ; 
 int /*<<< orphan*/  resolve_unique_section (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 
 int /*<<< orphan*/ * tls_comm_section ; 

__attribute__((used)) static section *
get_variable_section (tree decl, bool prefer_noswitch_p)
{
  int reloc;

  /* If the decl has been given an explicit section name, then it
     isn't common, and shouldn't be handled as such.  */
  if (DECL_COMMON (decl) && DECL_SECTION_NAME (decl) == NULL)
    {
      if (DECL_THREAD_LOCAL_P (decl))
	return tls_comm_section;
      if (TREE_PUBLIC (decl) && bss_initializer_p (decl))
	return comm_section;
    }

  if (DECL_INITIAL (decl) == error_mark_node)
    reloc = contains_pointers_p (TREE_TYPE (decl)) ? 3 : 0;
  else if (DECL_INITIAL (decl))
    reloc = compute_reloc_for_constant (DECL_INITIAL (decl));
  else
    reloc = 0;

  resolve_unique_section (decl, reloc, flag_data_sections);
  if (IN_NAMED_SECTION (decl))
    return get_named_section (decl, NULL, reloc);

  if (!DECL_THREAD_LOCAL_P (decl)
      && !(prefer_noswitch_p && targetm.have_switchable_bss_sections)
      && bss_initializer_p (decl))
    {
      if (!TREE_PUBLIC (decl))
	return lcomm_section;
      if (bss_noswitch_section)
	return bss_noswitch_section;
    }

  return targetm.asm_out.select_section (decl, reloc, DECL_ALIGN (decl));
}