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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;

/* Variables and functions */
 scalar_t__ reg_class_subset_p (int,int) ; 
 int reg_preferred_class (int) ; 

__attribute__((used)) static int
reg_meets_class_p (int reg, enum reg_class class)
{
  enum reg_class rclass = reg_preferred_class (reg);
  return (reg_class_subset_p (rclass, class)
	  || reg_class_subset_p (class, rclass));
}