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
struct net_device {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  WHITESPACE ; 
 char* aoe_iflist ; 
 int strcspn (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int strspn (char*,int /*<<< orphan*/ ) ; 

int
is_aoe_netif(struct net_device *ifp)
{
	register char *p, *q;
	register int len;

	if (aoe_iflist[0] == '\0')
		return 1;

	p = aoe_iflist + strspn(aoe_iflist, WHITESPACE);
	for (; *p; p = q + strspn(q, WHITESPACE)) {
		q = p + strcspn(p, WHITESPACE);
		if (q != p)
			len = q - p;
		else
			len = strlen(p); /* last token in aoe_iflist */

		if (strlen(ifp->name) == len && !strncmp(ifp->name, p, len))
			return 1;
		if (q == p)
			break;
	}

	return 0;
}