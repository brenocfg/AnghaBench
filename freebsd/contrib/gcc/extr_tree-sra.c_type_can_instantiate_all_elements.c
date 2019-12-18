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
#define  ARRAY_TYPE 130 
#define  COMPLEX_TYPE 129 
 int FIELD_DECL ; 
#define  RECORD_TYPE 128 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int TYPE_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ is_sra_scalar_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sra_type_can_be_decomposed_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sra_type_inst_cache ; 

__attribute__((used)) static bool
type_can_instantiate_all_elements (tree type)
{
  if (is_sra_scalar_type (type))
    return true;
  if (!sra_type_can_be_decomposed_p (type))
    return false;

  switch (TREE_CODE (type))
    {
    case RECORD_TYPE:
      {
	unsigned int cache = TYPE_UID (TYPE_MAIN_VARIANT (type)) * 2;
	tree f;

	if (bitmap_bit_p (sra_type_inst_cache, cache+0))
	  return true;
	if (bitmap_bit_p (sra_type_inst_cache, cache+1))
	  return false;

	for (f = TYPE_FIELDS (type); f ; f = TREE_CHAIN (f))
	  if (TREE_CODE (f) == FIELD_DECL)
	    {
	      if (!type_can_instantiate_all_elements (TREE_TYPE (f)))
		{
		  bitmap_set_bit (sra_type_inst_cache, cache+1);
		  return false;
		}
	    }

	bitmap_set_bit (sra_type_inst_cache, cache+0);
	return true;
      }

    case ARRAY_TYPE:
      return type_can_instantiate_all_elements (TREE_TYPE (type));

    case COMPLEX_TYPE:
      return true;

    default:
      gcc_unreachable ();
    }
}