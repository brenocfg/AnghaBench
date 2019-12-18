#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int slave; int sub; int data; } ;

/* Variables and functions */
 int i2c_count ; 
 TYPE_1__* i2cinfo ; 

__attribute__((used)) static int pms_i2c_read(int slave, int sub)
{
	int i=0;
	for(i=0;i<i2c_count;i++)
	{
		if(i2cinfo[i].slave==slave && i2cinfo[i].sub==sub)
			return i2cinfo[i].data;
	}
	return 0;
}