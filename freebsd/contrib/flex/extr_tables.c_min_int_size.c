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
struct yytbl_data {int dummy; } ;
typedef  scalar_t__ flex_uint32_t ;
typedef  int /*<<< orphan*/  flex_int8_t ;
typedef  scalar_t__ flex_int32_t ;
typedef  int /*<<< orphan*/  flex_int16_t ;

/* Variables and functions */
 scalar_t__ INT16_MAX ; 
 scalar_t__ INT8_MAX ; 
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 scalar_t__ yytbl_calc_total_len (struct yytbl_data*) ; 
 int /*<<< orphan*/  yytbl_data_geti (struct yytbl_data*,scalar_t__) ; 

__attribute__((used)) static size_t min_int_size (struct yytbl_data *tbl)
{
	flex_uint32_t i, total_len;
	flex_int32_t max = 0;

	total_len = yytbl_calc_total_len (tbl);

	for (i = 0; i < total_len; i++) {
		flex_int32_t n;

		n = abs (yytbl_data_geti (tbl, i));

		if (n > max)
			max = n;
	}

	if (max <= INT8_MAX)
		return sizeof (flex_int8_t);
	else if (max <= INT16_MAX)
		return sizeof (flex_int16_t);
	else
		return sizeof (flex_int32_t);
}