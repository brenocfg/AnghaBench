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
struct rtattr {int rta_type; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ RTA_DATA (struct rtattr*) ; 
 struct rtattr* RTA_NEXT (struct rtattr*,int) ; 
 scalar_t__ RTA_OK (struct rtattr*,int) ; 

__le16 dn_fib_get_attr16(struct rtattr *attr, int attrlen, int type)
{
	while(RTA_OK(attr,attrlen)) {
		if (attr->rta_type == type)
			return *(__le16*)RTA_DATA(attr);
		attr = RTA_NEXT(attr, attrlen);
	}

	return 0;
}