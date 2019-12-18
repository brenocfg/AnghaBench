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
typedef  int /*<<< orphan*/  IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  ixj_write_cid_bit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ixj_write_cid_seize(IXJ *j)
{
	int cnt;

	for (cnt = 0; cnt < 150; cnt++) {
		ixj_write_cid_bit(j, 0);
		ixj_write_cid_bit(j, 1);
	}
	for (cnt = 0; cnt < 180; cnt++) {
		ixj_write_cid_bit(j, 1);
	}
}