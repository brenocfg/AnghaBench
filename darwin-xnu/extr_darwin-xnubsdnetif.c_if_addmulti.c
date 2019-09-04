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
struct sockaddr {int dummy; } ;
struct ifnet {int dummy; } ;
struct ifmultiaddr {int dummy; } ;

/* Variables and functions */
 int if_addmulti_common (struct ifnet*,struct sockaddr const*,struct ifmultiaddr**,int /*<<< orphan*/ ) ; 

int
if_addmulti(struct ifnet *ifp, const struct sockaddr *sa,
    struct ifmultiaddr **retifma)
{
	return (if_addmulti_common(ifp, sa, retifma, 0));
}