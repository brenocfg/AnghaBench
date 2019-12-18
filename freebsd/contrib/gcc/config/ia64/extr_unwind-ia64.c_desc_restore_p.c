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
struct unw_reg_info {scalar_t__ val; scalar_t__ when; int /*<<< orphan*/  where; } ;

/* Variables and functions */
 scalar_t__ MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  UNW_WHERE_NONE ; 
 int decode_abreg (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc_is_active (unsigned char,scalar_t__,struct unw_state_record*) ; 

__attribute__((used)) static inline void
desc_restore_p (unsigned char qp, unw_word t, unsigned char abreg,
		struct unw_state_record *sr)
{
  struct unw_reg_info *r;

  if (! desc_is_active (qp, t, sr))
    return;

  r = sr->curr.reg + decode_abreg (abreg, 0);
  r->where = UNW_WHERE_NONE;
  r->when = sr->region_start + MIN ((int)t, sr->region_len - 1);
  r->val = 0;
}