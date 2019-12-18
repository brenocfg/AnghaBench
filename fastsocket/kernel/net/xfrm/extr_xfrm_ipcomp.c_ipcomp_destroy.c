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
struct xfrm_state {struct ipcomp_data* data; } ;
struct ipcomp_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipcomp_free_data (struct ipcomp_data*) ; 
 int /*<<< orphan*/  ipcomp_resource_mutex ; 
 int /*<<< orphan*/  kfree (struct ipcomp_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_state_delete_tunnel (struct xfrm_state*) ; 

void ipcomp_destroy(struct xfrm_state *x)
{
	struct ipcomp_data *ipcd = x->data;
	if (!ipcd)
		return;
	xfrm_state_delete_tunnel(x);
	mutex_lock(&ipcomp_resource_mutex);
	ipcomp_free_data(ipcd);
	mutex_unlock(&ipcomp_resource_mutex);
	kfree(ipcd);
}