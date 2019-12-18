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
typedef  size_t u8 ;
struct minstrel_sta_info {TYPE_1__* r; } ;
struct TYPE_2__ {scalar_t__ cur_tp; } ;

/* Variables and functions */
 int MAX_THR_RATES ; 
 int /*<<< orphan*/  memmove (size_t*,size_t*,int) ; 

__attribute__((used)) static inline void
minstrel_sort_best_tp_rates(struct minstrel_sta_info *mi, int i, u8 *tp_list)
{
	int j = MAX_THR_RATES;

	while (j > 0 && mi->r[i].cur_tp > mi->r[tp_list[j - 1]].cur_tp)
		j--;
	if (j < MAX_THR_RATES - 1)
		memmove(&tp_list[j + 1], &tp_list[j], MAX_THR_RATES - (j + 1));
	if (j < MAX_THR_RATES)
		tp_list[j] = i;
}