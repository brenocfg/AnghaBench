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
struct veth_lpar_connection {scalar_t__ num_events; size_t remote_lp; scalar_t__ num_ack_events; struct veth_lpar_connection* msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  HvLpEvent_Type_VirtualLan ; 
 int /*<<< orphan*/  kfree (struct veth_lpar_connection*) ; 
 int /*<<< orphan*/  mf_deallocate_lp_events (size_t,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** veth_cnx ; 

__attribute__((used)) static void veth_destroy_connection(struct veth_lpar_connection *cnx)
{
	if (!cnx)
		return;

	if (cnx->num_events > 0)
		mf_deallocate_lp_events(cnx->remote_lp,
				      HvLpEvent_Type_VirtualLan,
				      cnx->num_events,
				      NULL, NULL);
	if (cnx->num_ack_events > 0)
		mf_deallocate_lp_events(cnx->remote_lp,
				      HvLpEvent_Type_VirtualLan,
				      cnx->num_ack_events,
				      NULL, NULL);

	kfree(cnx->msgs);
	veth_cnx[cnx->remote_lp] = NULL;
	kfree(cnx);
}