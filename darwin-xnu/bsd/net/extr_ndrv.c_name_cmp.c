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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int /*<<< orphan*/  ifnet_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_unit (struct ifnet*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  sprint_d (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int strncmp (char*,char*,int) ; 

__attribute__((used)) static int name_cmp(struct ifnet *ifp, char *q)
{	char *r;
	int len;
	char buf[IFNAMSIZ];

	r = buf;
	len = strlen(ifnet_name(ifp));
	strlcpy(r, ifnet_name(ifp), IFNAMSIZ);
	r += len;
	sprint_d(ifnet_unit(ifp), r, IFNAMSIZ-(r-buf));
#if NDRV_DEBUG
	printf("Comparing %s, %s\n", buf, q);
#endif
	return(strncmp(buf, q, IFNAMSIZ));
}