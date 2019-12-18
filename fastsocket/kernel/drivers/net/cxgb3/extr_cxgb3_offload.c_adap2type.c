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
 int T3A ; 
 int T3B ; 
 int T3C ; 
#define  T3_REV_A 131 
#define  T3_REV_B 130 
#define  T3_REV_B2 129 
#define  T3_REV_C 128 

__attribute__((used)) static inline int adap2type(struct adapter *adapter)
{
	int type = 0;

	switch (adapter->params.rev) {
	case T3_REV_A:
		type = T3A;
		break;
	case T3_REV_B:
	case T3_REV_B2:
		type = T3B;
		break;
	case T3_REV_C:
		type = T3C;
		break;
	}
	return type;
}