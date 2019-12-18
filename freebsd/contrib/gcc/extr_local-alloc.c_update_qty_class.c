#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
struct TYPE_2__ {int min_class; int alternate_class; } ;

/* Variables and functions */
 TYPE_1__* qty ; 
 int reg_alternate_class (int) ; 
 scalar_t__ reg_class_subset_p (int,int) ; 
 int reg_preferred_class (int) ; 

__attribute__((used)) static void
update_qty_class (int qtyno, int reg)
{
  enum reg_class rclass = reg_preferred_class (reg);
  if (reg_class_subset_p (rclass, qty[qtyno].min_class))
    qty[qtyno].min_class = rclass;

  rclass = reg_alternate_class (reg);
  if (reg_class_subset_p (rclass, qty[qtyno].alternate_class))
    qty[qtyno].alternate_class = rclass;
}