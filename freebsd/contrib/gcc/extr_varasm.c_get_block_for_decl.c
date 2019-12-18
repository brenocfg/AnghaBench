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
typedef  int /*<<< orphan*/  tree ;
struct object_block {int dummy; } ;
typedef  int /*<<< orphan*/  section ;

/* Variables and functions */
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_ONE_ONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DECL_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 scalar_t__ SECTION_NOSWITCH ; 
 scalar_t__ SECTION_STYLE (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  align_variable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct object_block* get_block_for_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_variable_section (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  host_integerp (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct object_block *
get_block_for_decl (tree decl)
{
  section *sect;

  if (TREE_CODE (decl) == VAR_DECL)
    {
      /* The object must be defined in this translation unit.  */
      if (DECL_EXTERNAL (decl))
	return NULL;

      /* There's no point using object blocks for something that is
	 isolated by definition.  */
      if (DECL_ONE_ONLY (decl))
	return NULL;
    }

  /* We can only calculate block offsets if the decl has a known
     constant size.  */
  if (DECL_SIZE_UNIT (decl) == NULL)
    return NULL;
  if (!host_integerp (DECL_SIZE_UNIT (decl), 1))
    return NULL;

  /* Find out which section should contain DECL.  We cannot put it into
     an object block if it requires a standalone definition.  */
  if (TREE_CODE (decl) == VAR_DECL)
      align_variable (decl, 0);
  sect = get_variable_section (decl, true);
  if (SECTION_STYLE (sect) == SECTION_NOSWITCH)
    return NULL;

  return get_block_for_section (sect);
}