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
 scalar_t__ CLASSTYPE_NON_ZERO_INIT_P (scalar_t__) ; 
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_P (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ strip_array_types (scalar_t__) ; 

int
zero_init_p (tree t)
{
  t = strip_array_types (t);

  if (t == error_mark_node)
    return 1;

  /* NULL pointers to data members are initialized with -1.  */
  if (TYPE_PTRMEM_P (t))
    return 0;

  /* Classes that contain types that can't be zero-initialized, cannot
     be zero-initialized themselves.  */
  if (CLASS_TYPE_P (t) && CLASSTYPE_NON_ZERO_INIT_P (t))
    return 0;

  return 1;
}