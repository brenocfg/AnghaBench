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
typedef  int /*<<< orphan*/  substitution_identifier_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSTYPE_TI_ARGS (int /*<<< orphan*/  const) ; 
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/  const) ; 
 scalar_t__ DECL_P (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  DECL_TI_ARGS (int /*<<< orphan*/  const) ; 
 scalar_t__ TREE_VEC_ELT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TREE_VEC_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ char_type_node ; 
 int /*<<< orphan*/  is_std_substitution (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline int
is_std_substitution_char (const tree node,
			  const substitution_identifier_index_t index)
{
  tree args;
  /* Check NODE's name is ::std::identifier.  */
  if (!is_std_substitution (node, index))
    return 0;
  /* Figure out its template args.  */
  if (DECL_P (node))
    args = DECL_TI_ARGS (node);
  else if (CLASS_TYPE_P (node))
    args = CLASSTYPE_TI_ARGS (node);
  else
    /* Oops, not a template.  */
    return 0;
  /* NODE's template arg list should be <char>.  */
  return
    TREE_VEC_LENGTH (args) == 1
    && TREE_VEC_ELT (args, 0) == char_type_node;
}