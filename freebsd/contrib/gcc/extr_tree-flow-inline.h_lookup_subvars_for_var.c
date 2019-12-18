#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* var_ann_t ;
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  subvar_t ;
struct TYPE_4__ {int /*<<< orphan*/  subvars; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (TYPE_1__*) ; 
 TYPE_1__* var_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline subvar_t *
lookup_subvars_for_var (tree var)
{
  var_ann_t ann = var_ann (var);
  gcc_assert (ann);
  return &ann->subvars;
}