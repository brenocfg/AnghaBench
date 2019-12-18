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
struct xfrm_tunnel {struct xfrm_tunnel* next; } ;

/* Variables and functions */
 int ENOENT ; 
 struct xfrm_tunnel** fam_handlers (unsigned short) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  tunnel4_mutex ; 

int xfrm4_tunnel_deregister(struct xfrm_tunnel *handler, unsigned short family)
{
	struct xfrm_tunnel **pprev;
	int ret = -ENOENT;

	mutex_lock(&tunnel4_mutex);

	for (pprev = fam_handlers(family); *pprev; pprev = &(*pprev)->next) {
		if (*pprev == handler) {
			*pprev = handler->next;
			ret = 0;
			break;
		}
	}

	mutex_unlock(&tunnel4_mutex);

	synchronize_net();

	return ret;
}