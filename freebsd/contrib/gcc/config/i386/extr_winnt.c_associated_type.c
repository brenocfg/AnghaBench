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
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TYPE_P (scalar_t__) ; 

__attribute__((used)) static tree
associated_type (tree decl)
{
  return  (DECL_CONTEXT (decl) && TYPE_P (DECL_CONTEXT (decl)))
            ?  DECL_CONTEXT (decl) : NULL_TREE;
}