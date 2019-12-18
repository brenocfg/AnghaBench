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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  section ;
struct TYPE_2__ {scalar_t__ have_named_sections; } ;

/* Variables and functions */
 scalar_t__ DECL_SECTION_NAME (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/ * get_named_section (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ targetm ; 
 int /*<<< orphan*/ * text_section ; 

__attribute__((used)) static section *
hot_function_section (tree decl)
{
  if (decl != NULL_TREE
      && DECL_SECTION_NAME (decl) != NULL_TREE
      && targetm.have_named_sections)
    return get_named_section (decl, NULL, 0);
  else
    return text_section;
}