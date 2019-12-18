#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_5__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
typedef  TYPE_1__ double_int ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst_wide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ double_int_ext (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
double_int_to_tree (tree type, double_int cst)
{
  cst = double_int_ext (cst, TYPE_PRECISION (type), TYPE_UNSIGNED (type));

  return build_int_cst_wide (type, cst.low, cst.high);
}