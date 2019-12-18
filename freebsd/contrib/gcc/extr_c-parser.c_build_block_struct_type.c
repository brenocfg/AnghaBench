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
struct block_sema_info {scalar_t__ block_byref_decl_list; scalar_t__ block_ref_decl_list; TYPE_1__* prev_block_info; void* BlockHasCopyDispose; } ;
struct TYPE_2__ {void* BlockHasCopyDispose; } ;

/* Variables and functions */
 scalar_t__ COPYABLE_BYREF_LOCAL_VAR (scalar_t__) ; 
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 int /*<<< orphan*/  FIELD_DECL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RECORD_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 void* TRUE ; 
 int /*<<< orphan*/  TYPE_UNQUALIFIED ; 
 scalar_t__ block_requires_copying (scalar_t__) ; 
 int /*<<< orphan*/  build_block_descriptor_type (void*) ; 
 scalar_t__ build_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_build_qualified_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chainon (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  finish_struct (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  pop_from_top_level () ; 
 int /*<<< orphan*/  ptr_type_node ; 
 int /*<<< orphan*/  push_to_top_level () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ start_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
build_block_struct_type (struct block_sema_info * block_impl)
{
  tree field_decl_chain, field_decl, chain;
  char buffer[32];
  static int unique_count;
  tree block_struct_type;

  /* Check and see if this block is required to have a Copy/Dispose
     helper function. If yes, set BlockHasCopyDispose to TRUE. */
  for (chain = block_impl->block_ref_decl_list; chain;
	chain = TREE_CHAIN (chain))
    if (block_requires_copying (TREE_VALUE (chain)))
    {
      block_impl->BlockHasCopyDispose = TRUE;
      break;
    }

  /* Further check to see that we have __block variables which require
     Copy/Dispose helpers. */
  for (chain = block_impl->block_byref_decl_list; chain;
	chain = TREE_CHAIN (chain))
    if (COPYABLE_BYREF_LOCAL_VAR (TREE_VALUE (chain)))
      {
	block_impl->BlockHasCopyDispose = TRUE;
	break;
      }

  sprintf(buffer, "__block_literal_%d", ++unique_count);
  push_to_top_level ();
  block_struct_type = start_struct (RECORD_TYPE, get_identifier (buffer));
  
  /* void *__isa; */
  field_decl = build_decl (FIELD_DECL, get_identifier ("__isa"), ptr_type_node);
  field_decl_chain = field_decl;
  
  /* int __flags */
  field_decl = build_decl (FIELD_DECL, get_identifier ("__flags"),
			   integer_type_node);
  chainon (field_decl_chain, field_decl);

  /* int __reserved */
  field_decl = build_decl (FIELD_DECL, get_identifier ("__reserved"),
			   integer_type_node);
  chainon (field_decl_chain, field_decl);
  
  /* void *__FuncPtr; */
  field_decl = build_decl (FIELD_DECL, get_identifier ("__FuncPtr"), ptr_type_node);
  chainon (field_decl_chain, field_decl);

  /* struct __block_descriptor *__descriptor */
  field_decl = build_decl (FIELD_DECL, get_identifier ("__descriptor"),
			    build_block_descriptor_type (block_impl->BlockHasCopyDispose));
  chainon (field_decl_chain, field_decl);
  
  if (block_impl->BlockHasCopyDispose)
  {
    /* If inner block of a nested block has BlockHasCopyDispose, so
	does its outer block. */
    if (block_impl->prev_block_info)
      block_impl->prev_block_info->BlockHasCopyDispose = TRUE;
  }

  /* int x; // ref variable list ... */
  for (chain = block_impl->block_ref_decl_list; chain; chain = TREE_CHAIN (chain))
  {
    tree p = TREE_VALUE (chain);
    /* Note! const-ness of copied in variable must not be carried over to the
	type of the synthesized struct field. It prevents to assign to this
	field when copy constructor is synthesized. */
    field_decl = build_decl (FIELD_DECL, DECL_NAME (p),
			     c_build_qualified_type (TREE_TYPE (p),
			                             TYPE_UNQUALIFIED));
    chainon (field_decl_chain, field_decl);
  }

  /* int *y; // byref variable list */
  for (chain = block_impl->block_byref_decl_list; chain; chain = TREE_CHAIN (chain))
  {
    tree p = TREE_VALUE (chain);
    field_decl = build_decl (FIELD_DECL, DECL_NAME (p),
			     TREE_TYPE (p));
    chainon (field_decl_chain, field_decl);
  }
  pop_from_top_level ();
  finish_struct (block_struct_type, field_decl_chain, NULL_TREE);
  return block_struct_type;
}