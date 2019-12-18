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
struct tree_phi_node {int dummy; } ;
struct phi_arg_d {int dummy; } ;

/* Variables and functions */
 int ceil_log2 (size_t) ; 

__attribute__((used)) static int
ideal_phi_node_len (int len)
{
  size_t size, new_size;
  int log2, new_len;

  /* We do not support allocations of less than two PHI argument slots.  */
  if (len < 2)
    len = 2;

  /* Compute the number of bytes of the original request.  */
  size = sizeof (struct tree_phi_node) + (len - 1) * sizeof (struct phi_arg_d);

  /* Round it up to the next power of two.  */
  log2 = ceil_log2 (size);
  new_size = 1 << log2;

  /* Now compute and return the number of PHI argument slots given an
     ideal size allocation.  */
  new_len = len + (new_size - size) / sizeof (struct phi_arg_d);
  return new_len;
}