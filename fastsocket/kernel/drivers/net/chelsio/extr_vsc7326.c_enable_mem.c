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
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  bist_wr (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int enable_mem(adapter_t *adapter, int moduleid)
{
	/*enable mem*/
	(void) bist_wr(adapter,moduleid, 0x00, 0x00);
	return 0;
}