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
struct xfrm6_tunnel {struct xfrm6_tunnel* next; } ;

/* Variables and functions */
 unsigned short AF_INET6 ; 
 int ENOENT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 struct xfrm6_tunnel* tunnel46_handlers ; 
 struct xfrm6_tunnel* tunnel6_handlers ; 
 int /*<<< orphan*/  tunnel6_mutex ; 

int xfrm6_tunnel_deregister(struct xfrm6_tunnel *handler, unsigned short family)
{
	struct xfrm6_tunnel **pprev;
	int ret = -ENOENT;

	mutex_lock(&tunnel6_mutex);

	for (pprev = (family == AF_INET6) ? &tunnel6_handlers : &tunnel46_handlers;
	     *pprev; pprev = &(*pprev)->next) {
		if (*pprev == handler) {
			*pprev = handler->next;
			ret = 0;
			break;
		}
	}

	mutex_unlock(&tunnel6_mutex);

	synchronize_net();

	return ret;
}