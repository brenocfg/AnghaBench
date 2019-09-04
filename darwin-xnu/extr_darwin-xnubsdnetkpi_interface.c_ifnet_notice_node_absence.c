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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int sa_len; scalar_t__ sa_family; } ;
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_LINK ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  dlil_node_absent (int /*<<< orphan*/ *,struct sockaddr*) ; 

errno_t
ifnet_notice_node_absence(ifnet_t ifp, struct sockaddr *sa)
{
	if (ifp == NULL || sa == NULL)
		return (EINVAL);
	if (sa->sa_len > sizeof(struct sockaddr_storage))
		return (EINVAL);
	if (sa->sa_family != AF_LINK && sa->sa_family != AF_INET6)
		return (EINVAL);

	dlil_node_absent(ifp, sa);
	return (0);
}