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
typedef  scalar_t__ var_ann_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ create_var_ann (int /*<<< orphan*/ ) ; 
 scalar_t__ var_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline var_ann_t
get_var_ann (tree var)
{
  var_ann_t ann = var_ann (var);
  return (ann) ? ann : create_var_ann (var);
}