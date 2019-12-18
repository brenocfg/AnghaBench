#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_4__ {scalar_t__ type_shadowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_IDENTIFIER_TYPE_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_PURPOSE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 TYPE_1__* class_binding_level ; 
 TYPE_1__* previous_class_level ; 
 int /*<<< orphan*/  push_binding_level (TYPE_1__*) ; 

__attribute__((used)) static void
restore_class_cache (void)
{
  tree type;

  /* We are re-entering the same class we just left, so we don't
     have to search the whole inheritance matrix to find all the
     decls to bind again.  Instead, we install the cached
     class_shadowed list and walk through it binding names.  */
  push_binding_level (previous_class_level);
  class_binding_level = previous_class_level;
  /* Restore IDENTIFIER_TYPE_VALUE.  */
  for (type = class_binding_level->type_shadowed;
       type;
       type = TREE_CHAIN (type))
    SET_IDENTIFIER_TYPE_VALUE (TREE_PURPOSE (type), TREE_TYPE (type));
}