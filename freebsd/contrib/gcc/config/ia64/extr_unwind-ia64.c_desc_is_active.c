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
typedef  scalar_t__ unw_word ;
struct unw_state_record {scalar_t__ when_target; scalar_t__ region_start; unsigned long pr_val; unsigned long pr_mask; scalar_t__ region_len; } ;

/* Variables and functions */
 scalar_t__ MIN (int,scalar_t__) ; 

__attribute__((used)) static inline int
desc_is_active (unsigned char qp, unw_word t, struct unw_state_record *sr)
{
  if (sr->when_target <= sr->region_start + MIN ((int)t, sr->region_len - 1))
    return 0;
  if (qp > 0)
    {
      if ((sr->pr_val & (1UL << qp)) == 0) 
	return 0;
      sr->pr_mask |= (1UL << qp);
    }
  return 1;
}