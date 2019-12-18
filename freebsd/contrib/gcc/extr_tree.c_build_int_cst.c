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
typedef  int /*<<< orphan*/  tree ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  build_int_cst_wide (int /*<<< orphan*/ ,scalar_t__,int) ; 

tree
build_int_cst (tree type, HOST_WIDE_INT low)
{
  return build_int_cst_wide (type, low, low < 0 ? -1 : 0);
}