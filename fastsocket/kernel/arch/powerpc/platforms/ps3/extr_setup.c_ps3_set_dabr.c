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

/* Variables and functions */
 scalar_t__ lv1_set_dabr (unsigned long,int) ; 

__attribute__((used)) static int ps3_set_dabr(unsigned long dabr)
{
	enum {DABR_USER = 1, DABR_KERNEL = 2,};

	return lv1_set_dabr(dabr, DABR_KERNEL | DABR_USER) ? -1 : 0;
}