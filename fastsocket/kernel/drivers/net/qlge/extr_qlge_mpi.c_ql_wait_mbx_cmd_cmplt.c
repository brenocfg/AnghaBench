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
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  STS ; 
 int STS_PI ; 
 int /*<<< orphan*/  UDELAY_DELAY ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_wait_mbx_cmd_cmplt(struct ql_adapter *qdev)
{
	int count = 100;
	u32 value;

	do {
		value = ql_read32(qdev, STS);
		if (value & STS_PI)
			return 0;
		mdelay(UDELAY_DELAY); /* 100ms */
	} while (--count);
	return -ETIMEDOUT;
}