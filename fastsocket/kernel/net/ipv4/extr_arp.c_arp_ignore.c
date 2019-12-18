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
struct in_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int IN_DEV_ARP_IGNORE (struct in_device*) ; 
 int RT_SCOPE_HOST ; 
 int RT_SCOPE_LINK ; 
 int /*<<< orphan*/  inet_confirm_addr (struct in_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int arp_ignore(struct in_device *in_dev, __be32 sip, __be32 tip)
{
	int scope;

	switch (IN_DEV_ARP_IGNORE(in_dev)) {
	case 0:	/* Reply, the tip is already validated */
		return 0;
	case 1:	/* Reply only if tip is configured on the incoming interface */
		sip = 0;
		scope = RT_SCOPE_HOST;
		break;
	case 2:	/*
		 * Reply only if tip is configured on the incoming interface
		 * and is in same subnet as sip
		 */
		scope = RT_SCOPE_HOST;
		break;
	case 3:	/* Do not reply for scope host addresses */
		sip = 0;
		scope = RT_SCOPE_LINK;
		break;
	case 4:	/* Reserved */
	case 5:
	case 6:
	case 7:
		return 0;
	case 8:	/* Do not reply */
		return 1;
	default:
		return 0;
	}
	return !inet_confirm_addr(in_dev, sip, tip, scope);
}