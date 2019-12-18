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
typedef  int unw_word ;
struct TYPE_2__ {scalar_t__ reg; } ;
struct unw_state_record {scalar_t__ region_len; scalar_t__ region_start; TYPE_1__ curr; } ;

/* Variables and functions */
 scalar_t__ MIN (int,scalar_t__) ; 
 scalar_t__ UNW_REG_PSP ; 
 int /*<<< orphan*/  UNW_WHERE_NONE ; 
 int /*<<< orphan*/  set_reg (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static inline void
desc_mem_stack_f (unw_word t, unw_word size, struct unw_state_record *sr)
{
  set_reg (sr->curr.reg + UNW_REG_PSP, UNW_WHERE_NONE,
	   sr->region_start + MIN ((int)t, sr->region_len - 1), 16*size);
}