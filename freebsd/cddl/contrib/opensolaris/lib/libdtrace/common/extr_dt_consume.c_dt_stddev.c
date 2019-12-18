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
typedef  scalar_t__ uint64_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  dt_divide_128 (scalar_t__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  dt_multiply_128 (scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ dt_sqrt_128 (scalar_t__*) ; 
 int /*<<< orphan*/  dt_subtract_128 (scalar_t__*,scalar_t__*,scalar_t__*) ; 

uint64_t
dt_stddev(uint64_t *data, uint64_t normal)
{
	uint64_t avg_of_squares[2];
	uint64_t square_of_avg[2];
	int64_t norm_avg;
	uint64_t diff[2];

	if (data[0] == 0)
		return (0);

	/*
	 * The standard approximation for standard deviation is
	 * sqrt(average(x**2) - average(x)**2), i.e. the square root
	 * of the average of the squares minus the square of the average.
	 * When normalizing, we should divide the sum of x**2 by normal**2.
	 */
	dt_divide_128(data + 2, normal, avg_of_squares);
	dt_divide_128(avg_of_squares, normal, avg_of_squares);
	dt_divide_128(avg_of_squares, data[0], avg_of_squares);

	norm_avg = (int64_t)data[1] / (int64_t)normal / (int64_t)data[0];

	if (norm_avg < 0)
		norm_avg = -norm_avg;

	dt_multiply_128((uint64_t)norm_avg, (uint64_t)norm_avg, square_of_avg);

	dt_subtract_128(avg_of_squares, square_of_avg, diff);

	return (dt_sqrt_128(diff));
}