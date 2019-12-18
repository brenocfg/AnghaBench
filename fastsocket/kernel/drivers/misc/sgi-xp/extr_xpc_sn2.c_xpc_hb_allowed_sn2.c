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
 int test_bit (short,void*) ; 

__attribute__((used)) static int
xpc_hb_allowed_sn2(short partid, void *heartbeating_to_mask)
{
	return test_bit(partid, heartbeating_to_mask);
}