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
struct TYPE_2__ {int rev; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
#define  T3_REV_B 130 
#define  T3_REV_B2 129 
#define  T3_REV_C 128 

__attribute__((used)) static inline char t3rev2char(struct adapter *adapter)
{
	char rev = 0;

	switch(adapter->params.rev) {
	case T3_REV_B:
	case T3_REV_B2:
		rev = 'b';
		break;
	case T3_REV_C:
		rev = 'c';
		break;
	}
	return rev;
}