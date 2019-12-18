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
 int /*<<< orphan*/  carthw_ssf2_write8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ssf2_banks ; 

__attribute__((used)) static void carthw_ssf2_statef(void)
{
	int i;
	for (i = 1; i < 8; i++)
		carthw_ssf2_write8(0xa130f0 | (i << 1), ssf2_banks[i]);
}