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

/* Variables and functions */
#define  BOUND_TEMPLATE_TEMPLATE_PARM 131 
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TEMPLATE_PARM_DECL (int /*<<< orphan*/  const) ; 
 int TEMPLATE_PARM_IDX (int /*<<< orphan*/  const) ; 
#define  TEMPLATE_PARM_INDEX 130 
 int TEMPLATE_PARM_LEVEL (int /*<<< orphan*/  const) ; 
#define  TEMPLATE_TEMPLATE_PARM 129 
 int TEMPLATE_TYPE_IDX (int /*<<< orphan*/  const) ; 
 int TEMPLATE_TYPE_LEVEL (int /*<<< orphan*/  const) ; 
#define  TEMPLATE_TYPE_PARM 128 
 int TREE_CODE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_unsigned_number (int) ; 

__attribute__((used)) static void
write_template_param (const tree parm)
{
  int parm_index;
  int parm_level;
  tree parm_type = NULL_TREE;

  MANGLE_TRACE_TREE ("template-parm", parm);

  switch (TREE_CODE (parm))
    {
    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_TEMPLATE_PARM:
    case BOUND_TEMPLATE_TEMPLATE_PARM:
      parm_index = TEMPLATE_TYPE_IDX (parm);
      parm_level = TEMPLATE_TYPE_LEVEL (parm);
      break;

    case TEMPLATE_PARM_INDEX:
      parm_index = TEMPLATE_PARM_IDX (parm);
      parm_level = TEMPLATE_PARM_LEVEL (parm);
      parm_type = TREE_TYPE (TEMPLATE_PARM_DECL (parm));
      break;

    default:
      gcc_unreachable ();
    }

  write_char ('T');
  /* NUMBER as it appears in the mangling is (-1)-indexed, with the
     earliest template param denoted by `_'.  */
  if (parm_index > 0)
    write_unsigned_number (parm_index - 1);
  write_char ('_');
}