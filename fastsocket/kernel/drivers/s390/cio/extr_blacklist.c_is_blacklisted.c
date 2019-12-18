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
 int /*<<< orphan*/ * bl_dev ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

int
is_blacklisted (int ssid, int devno)
{
	return test_bit (devno, bl_dev[ssid]);
}