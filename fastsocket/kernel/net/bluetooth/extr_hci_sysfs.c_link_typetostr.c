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
#define  ACL_LINK 130 
#define  ESCO_LINK 129 
#define  SCO_LINK 128 

__attribute__((used)) static inline char *link_typetostr(int type)
{
	switch (type) {
	case ACL_LINK:
		return "ACL";
	case SCO_LINK:
		return "SCO";
	case ESCO_LINK:
		return "eSCO";
	default:
		return "UNKNOWN";
	}
}