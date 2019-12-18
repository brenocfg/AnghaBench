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
 scalar_t__ NULL_TREE ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ non_reference (scalar_t__) ; 

__attribute__((used)) static tree
prepare_eh_type (tree type)
{
  if (type == NULL_TREE)
    return type;
  if (type == error_mark_node)
    return error_mark_node;

  /* peel back references, so they match.  */
  type = non_reference (type);

  /* Peel off cv qualifiers.  */
  type = TYPE_MAIN_VARIANT (type);

  return type;
}