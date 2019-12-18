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
struct sht15_data {int const val_humid; } ;

/* Variables and functions */
 int sht15_calc_temp (struct sht15_data*) ; 

__attribute__((used)) static inline int sht15_calc_humid(struct sht15_data *data)
{
	int RHlinear; /* milli percent */
	int temp = sht15_calc_temp(data);

	const int c1 = -4;
	const int c2 = 40500; /* x 10 ^ -6 */
	const int c3 = -2800; /* x10 ^ -9 */

	RHlinear = c1*1000
		+ c2 * data->val_humid/1000
		+ (data->val_humid * data->val_humid * c3)/1000000;
	return (temp - 25000) * (10000 + 80 * data->val_humid)
		/ 1000000 + RHlinear;
}