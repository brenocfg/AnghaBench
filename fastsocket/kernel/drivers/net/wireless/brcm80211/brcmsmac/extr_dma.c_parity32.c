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
typedef  int u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */

__attribute__((used)) static u32 parity32(__le32 data)
{
	/* no swap needed for counting 1's */
	u32 par_data = *(u32 *)&data;

	par_data ^= par_data >> 16;
	par_data ^= par_data >> 8;
	par_data ^= par_data >> 4;
	par_data ^= par_data >> 2;
	par_data ^= par_data >> 1;

	return par_data & 1;
}