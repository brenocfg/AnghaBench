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
 scalar_t__ INTEGER_CST ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_NEEDS_CONSTRUCTING (scalar_t__) ; 
 scalar_t__ build_zero_init (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static tree
build_default_init (tree type, tree nelts)
{
  /* [dcl.init]:

    To default-initialize an object of type T means:

    --if T is a non-POD class type (clause _class_), the default construc-
      tor  for  T is called (and the initialization is ill-formed if T has
      no accessible default constructor);

    --if T is an array type, each element is default-initialized;

    --otherwise, the storage for the object is zero-initialized.

    A program that calls for default-initialization of an entity of refer-
    ence type is ill-formed.  */

  /* If TYPE_NEEDS_CONSTRUCTING is true, the caller is responsible for
     performing the initialization.  This is confusing in that some
     non-PODs do not have TYPE_NEEDS_CONSTRUCTING set.  (For example,
     a class with a pointer-to-data member as a non-static data member
     does not have TYPE_NEEDS_CONSTRUCTING set.)  Therefore, we end up
     passing non-PODs to build_zero_init below, which is contrary to
     the semantics quoted above from [dcl.init].

     It happens, however, that the behavior of the constructor the
     standard says we should have generated would be precisely the
     same as that obtained by calling build_zero_init below, so things
     work out OK.  */
  if (TYPE_NEEDS_CONSTRUCTING (type)
      || (nelts && TREE_CODE (nelts) != INTEGER_CST))
    return NULL_TREE;

  /* At this point, TYPE is either a POD class type, an array of POD
     classes, or something even more innocuous.  */
  return build_zero_init (type, nelts, /*static_storage_p=*/false);
}