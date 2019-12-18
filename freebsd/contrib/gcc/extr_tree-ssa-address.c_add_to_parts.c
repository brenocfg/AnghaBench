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
typedef  void* tree ;
struct mem_address {void* base; void* index; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLUS_EXPR ; 
 void* TREE_TYPE (void*) ; 
 void* fold_build2 (int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (void*,void*) ; 

__attribute__((used)) static void
add_to_parts (struct mem_address *parts, tree elt)
{
  tree type;

  if (!parts->index)
    {
      parts->index = elt;
      return;
    }

  if (!parts->base)
    {
      parts->base = elt;
      return;
    }

  /* Add ELT to base.  */
  type = TREE_TYPE (parts->base);
  parts->base = fold_build2 (PLUS_EXPR, type,
			     parts->base,
			     fold_convert (type, elt));
}