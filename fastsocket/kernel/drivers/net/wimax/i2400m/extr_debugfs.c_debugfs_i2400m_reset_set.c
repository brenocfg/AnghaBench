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
struct i2400m {int (* bus_reset ) (struct i2400m*,int) ;} ;
typedef  enum i2400m_reset_type { ____Placeholder_i2400m_reset_type } i2400m_reset_type ;

/* Variables and functions */
 int EINVAL ; 
#define  I2400M_RT_BUS 130 
#define  I2400M_RT_COLD 129 
#define  I2400M_RT_WARM 128 
 int stub1 (struct i2400m*,int) ; 

__attribute__((used)) static
int debugfs_i2400m_reset_set(void *data, u64 val)
{
	int result;
	struct i2400m *i2400m = data;
	enum i2400m_reset_type rt = val;
	switch(rt) {
	case I2400M_RT_WARM:
	case I2400M_RT_COLD:
	case I2400M_RT_BUS:
		result = i2400m->bus_reset(i2400m, rt);
		if (result >= 0)
			result = 0;
	default:
		result = -EINVAL;
	}
	return result;
}