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
typedef  scalar_t__ unw_word ;
struct TYPE_2__ {struct unw_reg_info* reg; } ;
struct unw_state_record {scalar_t__ region_len; scalar_t__ region_start; TYPE_1__ curr; } ;
struct unw_reg_info {scalar_t__ where; scalar_t__ when; } ;

/* Variables and functions */
 scalar_t__ MIN (int,scalar_t__) ; 
 scalar_t__ UNW_WHERE_GR_SAVE ; 
 scalar_t__ UNW_WHERE_NONE ; 

__attribute__((used)) static inline void
desc_reg_when (unsigned char regnum, unw_word t, struct unw_state_record *sr)
{
  struct unw_reg_info *reg = sr->curr.reg + regnum;

  if (reg->where == UNW_WHERE_NONE)
    reg->where = UNW_WHERE_GR_SAVE;
  reg->when = sr->region_start + MIN ((int)t, sr->region_len - 1);
}