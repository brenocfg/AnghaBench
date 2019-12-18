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
struct unw_reg_info {unsigned long val; int where; int when; } ;
typedef  enum unw_where { ____Placeholder_unw_where } unw_where ;

/* Variables and functions */
 int UNW_WHEN_NEVER ; 

__attribute__((used)) static void
set_reg (struct unw_reg_info *reg, enum unw_where where,
	 int when, unsigned long val)
{
  reg->val = val;
  reg->where = where;
  if (reg->when == UNW_WHEN_NEVER)
    reg->when = when;
}