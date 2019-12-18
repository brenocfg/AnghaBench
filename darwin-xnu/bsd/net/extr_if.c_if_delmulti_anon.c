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

/* Variables and functions */
 int if_delmulti_common (int /*<<< orphan*/ *,struct ifnet*,struct sockaddr const*,int) ; 

int
if_delmulti_anon(struct ifnet *ifp, const struct sockaddr *sa)
{
	return (if_delmulti_common(NULL, ifp, sa, 1));
}