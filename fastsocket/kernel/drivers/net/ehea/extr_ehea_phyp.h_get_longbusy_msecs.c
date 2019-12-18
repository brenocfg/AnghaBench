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

/* Variables and functions */
#define  H_LONG_BUSY_ORDER_100_MSEC 133 
#define  H_LONG_BUSY_ORDER_100_SEC 132 
#define  H_LONG_BUSY_ORDER_10_MSEC 131 
#define  H_LONG_BUSY_ORDER_10_SEC 130 
#define  H_LONG_BUSY_ORDER_1_MSEC 129 
#define  H_LONG_BUSY_ORDER_1_SEC 128 

__attribute__((used)) static inline u32 get_longbusy_msecs(int long_busy_ret_code)
{
	switch (long_busy_ret_code) {
	case H_LONG_BUSY_ORDER_1_MSEC:
		return 1;
	case H_LONG_BUSY_ORDER_10_MSEC:
		return 10;
	case H_LONG_BUSY_ORDER_100_MSEC:
		return 100;
	case H_LONG_BUSY_ORDER_1_SEC:
		return 1000;
	case H_LONG_BUSY_ORDER_10_SEC:
		return 10000;
	case H_LONG_BUSY_ORDER_100_SEC:
		return 100000;
	default:
		return 1;
	}
}