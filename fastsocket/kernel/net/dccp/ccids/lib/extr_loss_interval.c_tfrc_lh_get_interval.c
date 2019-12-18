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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tfrc_loss_hist {scalar_t__ const counter; TYPE_1__** ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  li_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t LIH_INDEX (scalar_t__ const) ; 

__attribute__((used)) static inline u32 tfrc_lh_get_interval(struct tfrc_loss_hist *lh, const u8 i)
{
	BUG_ON(i >= lh->counter);
	return lh->ring[LIH_INDEX(lh->counter - i - 1)]->li_length;
}