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
struct yytbl_data {int td_lolen; int td_hilen; scalar_t__ td_id; } ;
typedef  int flex_int32_t ;

/* Variables and functions */
 scalar_t__ YYTD_ID_TRANSITION ; 

flex_int32_t yytbl_calc_total_len (const struct yytbl_data *tbl)
{
	flex_int32_t n;

	/* total number of ints */
	n = tbl->td_lolen;
	if (tbl->td_hilen > 0)
		n *= tbl->td_hilen;

	if (tbl->td_id == YYTD_ID_TRANSITION)
		n *= 2;
	return n;
}