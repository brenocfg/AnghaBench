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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  idct_column_false_mmi (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idct_column_true_mmi (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idct_row_mmi (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idct_mmi(uint8_t *dst, int stride, int16_t *input, int type)
{
    idct_row_mmi(input);
    if (type == 1)
        idct_column_true_mmi(dst, stride, input);
    else
        idct_column_false_mmi(dst, stride, input);
}