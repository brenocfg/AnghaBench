#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
struct TYPE_8__ {int /*<<< orphan*/  src_fn; int /*<<< orphan*/  decl_map; } ;
typedef  TYPE_2__ copy_body_data ;
struct TYPE_7__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  insert_decl_map (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * remap_type_1 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  variably_modified_type_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

tree
remap_type (tree type, copy_body_data *id)
{
  splay_tree_node node;

  if (type == NULL)
    return type;

  /* See if we have remapped this type.  */
  node = splay_tree_lookup (id->decl_map, (splay_tree_key) type);
  if (node)
    return (tree) node->value;

  /* The type only needs remapping if it's variably modified.  */
  if (! variably_modified_type_p (type, id->src_fn))
    {
      insert_decl_map (id, type, type);
      return type;
    }

  return remap_type_1 (type, id);
}