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
typedef  int /*<<< orphan*/  u32 ;
struct ar9170 {int dummy; } ;

/* Variables and functions */
 int carl9170_read_mreg (struct ar9170*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int carl9170_read_reg(struct ar9170 *ar, u32 reg, u32 *val)
{
	return carl9170_read_mreg(ar, 1, &reg, val);
}