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
#define  IP6_MH_TYPE_BACK 135 
#define  IP6_MH_TYPE_BERROR 134 
#define  IP6_MH_TYPE_BRR 133 
#define  IP6_MH_TYPE_BU 132 
#define  IP6_MH_TYPE_COT 131 
#define  IP6_MH_TYPE_COTI 130 
#define  IP6_MH_TYPE_HOT 129 
#define  IP6_MH_TYPE_HOTI 128 

__attribute__((used)) static int mip6_mh_len(int type)
{
	int len = 0;

	switch (type) {
	case IP6_MH_TYPE_BRR:
		len = 0;
		break;
	case IP6_MH_TYPE_HOTI:
	case IP6_MH_TYPE_COTI:
	case IP6_MH_TYPE_BU:
	case IP6_MH_TYPE_BACK:
		len = 1;
		break;
	case IP6_MH_TYPE_HOT:
	case IP6_MH_TYPE_COT:
	case IP6_MH_TYPE_BERROR:
		len = 2;
		break;
	}
	return len;
}