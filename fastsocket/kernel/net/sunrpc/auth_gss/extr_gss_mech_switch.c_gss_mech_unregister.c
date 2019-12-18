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
struct gss_api_mech {int /*<<< orphan*/  gm_name; int /*<<< orphan*/  gm_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_mech_free (struct gss_api_mech*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  registered_mechs_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
gss_mech_unregister(struct gss_api_mech *gm)
{
	spin_lock(&registered_mechs_lock);
	list_del(&gm->gm_list);
	spin_unlock(&registered_mechs_lock);
	dprintk("RPC:       unregistered gss mechanism %s\n", gm->gm_name);
	gss_mech_free(gm);
}