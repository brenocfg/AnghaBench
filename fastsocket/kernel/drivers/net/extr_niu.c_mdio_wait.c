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
typedef  int u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MIF_FRAME_OUTPUT ; 
 int MIF_FRAME_OUTPUT_DATA ; 
 int MIF_FRAME_OUTPUT_TA_SHIFT ; 
 int nr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mdio_wait(struct niu *np)
{
	int limit = 1000;
	u64 val;

	while (--limit > 0) {
		val = nr64(MIF_FRAME_OUTPUT);
		if ((val >> MIF_FRAME_OUTPUT_TA_SHIFT) & 0x1)
			return val & MIF_FRAME_OUTPUT_DATA;

		udelay(10);
	}

	return -ENODEV;
}