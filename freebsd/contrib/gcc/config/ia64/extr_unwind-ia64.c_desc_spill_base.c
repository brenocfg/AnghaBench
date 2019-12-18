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
typedef  int unw_word ;
struct unw_state_record {int spill_offset; } ;

/* Variables and functions */

__attribute__((used)) static inline void
desc_spill_base (unw_word pspoff, struct unw_state_record *sr)
{
  sr->spill_offset = 0x10 - 4*pspoff;
}