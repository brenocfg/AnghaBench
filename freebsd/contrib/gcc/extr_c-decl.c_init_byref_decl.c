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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 int BLOCK_ALIGN_MAX ; 
 int BLOCK_BYREF_CURRENT_MAX ; 
 int BLOCK_FIELD_IS_WEAK ; 
 unsigned int BLOCK_HAS_COPY_DISPOSE ; 
 scalar_t__ COPYABLE_BYREF_LOCAL_NONPOD (scalar_t__) ; 
 int DECL_ALIGN (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int TYPE_ALIGN (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (scalar_t__) ; 
 scalar_t__* block_byref_id_object_copy ; 
 scalar_t__* block_byref_id_object_dispose ; 
 scalar_t__ build_constructor_from_list (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_fold_addr_expr (scalar_t__) ; 
 scalar_t__ build_function_type (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_helper_func_decl (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_int_cst (scalar_t__,int) ; 
 scalar_t__ build_unary_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ do_digest_init (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 int exact_log2 (int) ; 
 scalar_t__ fold_convert (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  nreverse (scalar_t__) ; 
 scalar_t__ ptr_type_node ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  synth_block_byref_id_object_copy_func (int,int) ; 
 int /*<<< orphan*/  synth_block_byref_id_object_dispose_func (int,int) ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ void_list_node ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static tree
/* APPLE LOCAL radar 5847976 */
init_byref_decl (tree decl, tree init, int flag)
{
  tree initlist;
  tree block_byref_type = TREE_TYPE (decl);
  int size = TREE_INT_CST_LOW (TYPE_SIZE_UNIT (block_byref_type));
  unsigned flags = 0;
  tree fields;

  if (COPYABLE_BYREF_LOCAL_NONPOD (decl))
    flags = BLOCK_HAS_COPY_DISPOSE;

  fields = TYPE_FIELDS (block_byref_type);
  /* APPLE LOCAL begin radar 6244520 */
  /* APPLE LOCAL begin radar 5847976 */
  initlist = tree_cons (fields, fold_convert (ptr_type_node, ((flag & BLOCK_FIELD_IS_WEAK) != 0) ? integer_one_node 
									        : integer_zero_node), 0);
  /* APPLE LOCAL end radar 5847976 */
  fields = TREE_CHAIN (fields);

  initlist = tree_cons (fields,
			 build_unary_op (ADDR_EXPR, decl, 0), initlist);
   /* APPLE LOCAL end radar 6244520 */
  fields = TREE_CHAIN (fields);

  initlist = tree_cons (fields, build_int_cst (TREE_TYPE (fields), flags),
			 initlist);
  fields = TREE_CHAIN (fields);
  initlist = tree_cons (fields, build_int_cst (TREE_TYPE (fields), size),
			 initlist);
  fields = TREE_CHAIN (fields);

  if (COPYABLE_BYREF_LOCAL_NONPOD (decl))
    {
      char name[64];
      int align = exact_log2 ((DECL_ALIGN (decl)+TYPE_ALIGN (ptr_type_node)-1) / TYPE_ALIGN (ptr_type_node));
      int kind;
      if (align == -1 || align > BLOCK_ALIGN_MAX) {
	error ("invalid alignment for __block variable");
	kind = 0;
      } else
	kind = align*BLOCK_BYREF_CURRENT_MAX + flag;
      /* Add &__Block_byref_id_object_copy, &__Block_byref_id_object_dispose
	 initializers. */
      if (!block_byref_id_object_copy[kind])
	{
	  /* Build a void __Block_byref_id_object_copy(void*, void*) type. */
	  tree func_type =
	    build_function_type (void_type_node,
				 tree_cons (NULL_TREE, ptr_type_node,
					    tree_cons (NULL_TREE, ptr_type_node,
						       void_list_node)));
	  sprintf (name, "__Block_byref_id_object_copy%d", kind);
	  block_byref_id_object_copy[kind] = build_helper_func_decl (get_identifier (name),
								     func_type);
	  /* Synthesize function definition. */
	  synth_block_byref_id_object_copy_func (flag, kind);
	}
      initlist = tree_cons (fields,
			    build_fold_addr_expr (block_byref_id_object_copy[kind]),
			    initlist);
      fields = TREE_CHAIN (fields);

      if (!block_byref_id_object_dispose[kind])
	{
	  /* Synthesize void __Block_byref_id_object_dispose (void*) and
	     build &__Block_byref_id_object_dispose. */
	  tree func_type =
	    build_function_type (void_type_node,
				 tree_cons (NULL_TREE, ptr_type_node, void_list_node));
	  sprintf (name, "__Block_byref_id_object_dispose%d", kind);
	  block_byref_id_object_dispose[kind] = build_helper_func_decl (get_identifier (name),
									func_type);
	  /* Synthesize function definition. */
	  synth_block_byref_id_object_dispose_func (flag, kind);
	}
      initlist = tree_cons (fields,
			    build_fold_addr_expr (block_byref_id_object_dispose[kind]),
			    initlist);
      fields = TREE_CHAIN (fields);
    }

  if (init)
    {
      init = do_digest_init (TREE_TYPE (fields), init);
      initlist = tree_cons (fields, init, initlist);
    }
  init =  build_constructor_from_list (block_byref_type, nreverse (initlist));
  return init;
}