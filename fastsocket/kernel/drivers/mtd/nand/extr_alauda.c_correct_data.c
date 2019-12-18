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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  nand_calculate_ecc (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int nand_correct_data (int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void correct_data(void *buf, void *read_ecc,
		int *corrected, int *uncorrected)
{
	u8 calc_ecc[3];
	int err;

	nand_calculate_ecc(NULL, buf, calc_ecc);
	err = nand_correct_data(NULL, buf, read_ecc, calc_ecc);
	if (err) {
		if (err > 0)
			(*corrected)++;
		else
			(*uncorrected)++;
	}
}