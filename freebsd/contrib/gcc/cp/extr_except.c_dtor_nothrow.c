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
 int /*<<< orphan*/  CLASSTYPE_DESTRUCTORS (scalar_t__) ; 
 scalar_t__ CLASSTYPE_LAZY_DESTRUCTOR (scalar_t__) ; 
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int TREE_NOTHROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lazily_declare_fn (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sfk_destructor ; 

__attribute__((used)) static int
dtor_nothrow (tree type)
{
  if (type == NULL_TREE)
    return 0;

  if (!CLASS_TYPE_P (type))
    return 1;

  if (CLASSTYPE_LAZY_DESTRUCTOR (type))
    lazily_declare_fn (sfk_destructor, type);

  return TREE_NOTHROW (CLASSTYPE_DESTRUCTORS (type));
}