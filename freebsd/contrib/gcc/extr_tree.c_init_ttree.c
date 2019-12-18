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
struct TYPE_2__ {int /*<<< orphan*/  (* init_ts ) () ;} ;

/* Variables and functions */
 size_t CONST_DECL ; 
 size_t FIELD_DECL ; 
 size_t FUNCTION_DECL ; 
 int /*<<< orphan*/  INTEGER_CST ; 
 size_t LABEL_DECL ; 
 size_t NAME_MEMORY_TAG ; 
 size_t PARM_DECL ; 
 size_t RESULT_DECL ; 
 size_t STRUCT_FIELD_TAG ; 
 size_t SYMBOL_MEMORY_TAG ; 
 size_t TRANSLATION_UNIT_DECL ; 
 size_t TS_CONST_DECL ; 
 size_t TS_DECL_COMMON ; 
 size_t TS_DECL_MINIMAL ; 
 size_t TS_DECL_NON_COMMON ; 
 size_t TS_DECL_WITH_VIS ; 
 size_t TS_DECL_WRTL ; 
 size_t TS_FIELD_DECL ; 
 size_t TS_FUNCTION_DECL ; 
 size_t TS_LABEL_DECL ; 
 size_t TS_MEMORY_TAG ; 
 size_t TS_PARM_DECL ; 
 size_t TS_RESULT_DECL ; 
 size_t TS_STRUCT_FIELD_TAG ; 
 size_t TS_TYPE_DECL ; 
 size_t TS_VAR_DECL ; 
 size_t TYPE_DECL ; 
 int TYPE_HASH_INITIAL_SIZE ; 
 size_t VAR_DECL ; 
 void* debug_expr_for_decl ; 
 void* htab_create_ggc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* init_priority_for_decl ; 
 int /*<<< orphan*/  int_cst_hash_eq ; 
 int /*<<< orphan*/  int_cst_hash_hash ; 
 void* int_cst_hash_table ; 
 int /*<<< orphan*/  int_cst_node ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  make_node (int /*<<< orphan*/ ) ; 
 void* restrict_base_for_decl ; 
 int /*<<< orphan*/  stub1 () ; 
 int** tree_contains_struct ; 
 int /*<<< orphan*/  tree_int_map_eq ; 
 int /*<<< orphan*/  tree_int_map_hash ; 
 int /*<<< orphan*/  tree_map_eq ; 
 int /*<<< orphan*/  tree_map_hash ; 
 int /*<<< orphan*/  type_hash_eq ; 
 int /*<<< orphan*/  type_hash_hash ; 
 void* type_hash_table ; 
 void* value_expr_for_decl ; 

void
init_ttree (void)
{
  /* Initialize the hash table of types.  */
  type_hash_table = htab_create_ggc (TYPE_HASH_INITIAL_SIZE, type_hash_hash,
				     type_hash_eq, 0);

  debug_expr_for_decl = htab_create_ggc (512, tree_map_hash,
					 tree_map_eq, 0);

  value_expr_for_decl = htab_create_ggc (512, tree_map_hash,
					 tree_map_eq, 0);
  init_priority_for_decl = htab_create_ggc (512, tree_int_map_hash,
					    tree_int_map_eq, 0);
  restrict_base_for_decl = htab_create_ggc (256, tree_map_hash,
					    tree_map_eq, 0);

  int_cst_hash_table = htab_create_ggc (1024, int_cst_hash_hash,
					int_cst_hash_eq, NULL);
  
  int_cst_node = make_node (INTEGER_CST);

  tree_contains_struct[FUNCTION_DECL][TS_DECL_NON_COMMON] = 1;
  tree_contains_struct[TRANSLATION_UNIT_DECL][TS_DECL_NON_COMMON] = 1;
  tree_contains_struct[TYPE_DECL][TS_DECL_NON_COMMON] = 1;
  

  tree_contains_struct[CONST_DECL][TS_DECL_COMMON] = 1;
  tree_contains_struct[VAR_DECL][TS_DECL_COMMON] = 1;
  tree_contains_struct[PARM_DECL][TS_DECL_COMMON] = 1;
  tree_contains_struct[RESULT_DECL][TS_DECL_COMMON] = 1;
  tree_contains_struct[FUNCTION_DECL][TS_DECL_COMMON] = 1;
  tree_contains_struct[TYPE_DECL][TS_DECL_COMMON] = 1;
  tree_contains_struct[TRANSLATION_UNIT_DECL][TS_DECL_COMMON] = 1;
  tree_contains_struct[LABEL_DECL][TS_DECL_COMMON] = 1;
  tree_contains_struct[FIELD_DECL][TS_DECL_COMMON] = 1;


  tree_contains_struct[CONST_DECL][TS_DECL_WRTL] = 1;
  tree_contains_struct[VAR_DECL][TS_DECL_WRTL] = 1;
  tree_contains_struct[PARM_DECL][TS_DECL_WRTL] = 1;
  tree_contains_struct[RESULT_DECL][TS_DECL_WRTL] = 1;
  tree_contains_struct[FUNCTION_DECL][TS_DECL_WRTL] = 1;
  tree_contains_struct[LABEL_DECL][TS_DECL_WRTL] = 1; 

  tree_contains_struct[CONST_DECL][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[VAR_DECL][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[PARM_DECL][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[RESULT_DECL][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[FUNCTION_DECL][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[TYPE_DECL][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[TRANSLATION_UNIT_DECL][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[LABEL_DECL][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[FIELD_DECL][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[STRUCT_FIELD_TAG][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[NAME_MEMORY_TAG][TS_DECL_MINIMAL] = 1;
  tree_contains_struct[SYMBOL_MEMORY_TAG][TS_DECL_MINIMAL] = 1;

  tree_contains_struct[STRUCT_FIELD_TAG][TS_MEMORY_TAG] = 1;
  tree_contains_struct[NAME_MEMORY_TAG][TS_MEMORY_TAG] = 1;
  tree_contains_struct[SYMBOL_MEMORY_TAG][TS_MEMORY_TAG] = 1;

  tree_contains_struct[STRUCT_FIELD_TAG][TS_STRUCT_FIELD_TAG] = 1;

  tree_contains_struct[VAR_DECL][TS_DECL_WITH_VIS] = 1;
  tree_contains_struct[FUNCTION_DECL][TS_DECL_WITH_VIS] = 1;
  tree_contains_struct[TYPE_DECL][TS_DECL_WITH_VIS] = 1;
  tree_contains_struct[TRANSLATION_UNIT_DECL][TS_DECL_WITH_VIS] = 1;
  
  tree_contains_struct[VAR_DECL][TS_VAR_DECL] = 1;
  tree_contains_struct[FIELD_DECL][TS_FIELD_DECL] = 1;
  tree_contains_struct[PARM_DECL][TS_PARM_DECL] = 1;
  tree_contains_struct[LABEL_DECL][TS_LABEL_DECL] = 1;
  tree_contains_struct[RESULT_DECL][TS_RESULT_DECL] = 1;
  tree_contains_struct[CONST_DECL][TS_CONST_DECL] = 1;
  tree_contains_struct[TYPE_DECL][TS_TYPE_DECL] = 1;
  tree_contains_struct[FUNCTION_DECL][TS_FUNCTION_DECL] = 1;

  lang_hooks.init_ts ();
}