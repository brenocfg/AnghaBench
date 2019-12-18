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
struct tfrc_loss_interval {int dummy; } ;
struct tfrc_loss_hist {scalar_t__ counter; struct tfrc_loss_interval** ring; } ;

/* Variables and functions */
 size_t LIH_INDEX (scalar_t__) ; 

__attribute__((used)) static inline struct tfrc_loss_interval *tfrc_lh_peek(struct tfrc_loss_hist *lh)
{
	return lh->counter ? lh->ring[LIH_INDEX(lh->counter - 1)] : NULL;
}