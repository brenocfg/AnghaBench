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
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int EPERM ; 
#define  H_BUSY 138 
#define  H_FUNCTION 137 
#define  H_HARDWARE 136 
#define  H_LONG_BUSY_ORDER_100_MSEC 135 
#define  H_LONG_BUSY_ORDER_100_SEC 134 
#define  H_LONG_BUSY_ORDER_10_MSEC 133 
#define  H_LONG_BUSY_ORDER_10_SEC 132 
#define  H_LONG_BUSY_ORDER_1_MSEC 131 
#define  H_LONG_BUSY_ORDER_1_SEC 130 
#define  H_PARAMETER 129 
#define  H_SUCCESS 128 

__attribute__((used)) static int hvcs_convert(long to_convert)
{
	switch (to_convert) {
		case H_SUCCESS:
			return 0;
		case H_PARAMETER:
			return -EINVAL;
		case H_HARDWARE:
			return -EIO;
		case H_BUSY:
		case H_LONG_BUSY_ORDER_1_MSEC:
		case H_LONG_BUSY_ORDER_10_MSEC:
		case H_LONG_BUSY_ORDER_100_MSEC:
		case H_LONG_BUSY_ORDER_1_SEC:
		case H_LONG_BUSY_ORDER_10_SEC:
		case H_LONG_BUSY_ORDER_100_SEC:
			return -EBUSY;
		case H_FUNCTION: /* fall through */
		default:
			return -EPERM;
	}
}