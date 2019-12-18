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
typedef  enum i2c_status { ____Placeholder_i2c_status } i2c_status ;

/* Variables and functions */
#define  ARB_LOST 133 
#define  BUS_ERR 132 
#define  NO_ACKN 131 
#define  NO_DEVICE 130 
#define  SEQ_ERR 129 
#define  ST_ERR 128 

__attribute__((used)) static inline int i2c_is_error(enum i2c_status status)
{
	switch (status) {
	case NO_DEVICE:
	case NO_ACKN:
	case BUS_ERR:
	case ARB_LOST:
	case SEQ_ERR:
	case ST_ERR:
		return true;
	default:
		return false;
	}
}