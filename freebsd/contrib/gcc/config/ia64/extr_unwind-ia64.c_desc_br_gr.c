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
struct TYPE_2__ {scalar_t__ reg; } ;
struct unw_state_record {scalar_t__ region_len; scalar_t__ region_start; TYPE_1__ curr; } ;

/* Variables and functions */
 scalar_t__ UNW_REG_B1 ; 
 int /*<<< orphan*/  UNW_WHERE_GR ; 
 int /*<<< orphan*/  set_reg (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
desc_br_gr (unsigned char brmask, unsigned char gr,
	    struct unw_state_record *sr)
{
  int i;

  for (i = 0; i < 5; ++i)
    {
      if (brmask & 1)
	set_reg (sr->curr.reg + UNW_REG_B1 + i, UNW_WHERE_GR,
		 sr->region_start + sr->region_len - 1, gr++);
      brmask >>= 1;
    }
}