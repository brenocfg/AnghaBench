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
struct hwblk_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwblk_mod_cnt (struct hwblk_info*,int,int,int,int /*<<< orphan*/ ) ; 

void hwblk_cnt_dec(struct hwblk_info *info, int hwblk, int counter)
{
	hwblk_mod_cnt(info, hwblk, counter, -1, 0);
}