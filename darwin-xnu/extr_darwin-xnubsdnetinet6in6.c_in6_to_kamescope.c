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
struct sockaddr_in6 {int sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int in6_addr2scopeid (struct ifnet*,int /*<<< orphan*/ *) ; 
 int in6_embedscope (int /*<<< orphan*/ *,struct sockaddr_in6*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int in6_recoverscope (struct sockaddr_in6*,int /*<<< orphan*/ *,struct ifnet*) ; 

__attribute__((used)) static int
in6_to_kamescope(struct sockaddr_in6 *sin6, struct ifnet *ifp)
{
	struct sockaddr_in6 tmp;
	int error, id;

	VERIFY(sin6 != NULL);
	tmp = *sin6;

	error = in6_recoverscope(&tmp, &sin6->sin6_addr, ifp);
	if (error != 0)
		return (error);

	id = in6_addr2scopeid(ifp, &tmp.sin6_addr);
	if (tmp.sin6_scope_id == 0)
		tmp.sin6_scope_id = id;
	else if (tmp.sin6_scope_id != id)
		return (EINVAL); /* scope ID mismatch. */

	error = in6_embedscope(&tmp.sin6_addr, &tmp, NULL, NULL, NULL);
	if (error != 0)
		return (error);

	tmp.sin6_scope_id = 0;
	*sin6 = tmp;
	return (0);
}