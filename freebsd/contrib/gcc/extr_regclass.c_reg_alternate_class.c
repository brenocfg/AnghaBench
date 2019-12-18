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
struct TYPE_2__ {int /*<<< orphan*/  altclass; } ;

/* Variables and functions */
 int ALL_REGS ; 
 TYPE_1__* reg_pref ; 

enum reg_class
reg_alternate_class (int regno)
{
  if (reg_pref == 0)
    return ALL_REGS;

  return (enum reg_class) reg_pref[regno].altclass;
}