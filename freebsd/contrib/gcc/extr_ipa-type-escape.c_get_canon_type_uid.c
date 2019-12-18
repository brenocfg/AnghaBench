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
 int TYPE_UID (scalar_t__) ; 
 scalar_t__ get_canon_type (scalar_t__,int,int) ; 

__attribute__((used)) static int
get_canon_type_uid (tree type, bool see_thru_ptrs, bool see_thru_arrays)
{
  type = get_canon_type (type, see_thru_ptrs, see_thru_arrays);
  if (type)
    return TYPE_UID(type);
  else return 0;
}