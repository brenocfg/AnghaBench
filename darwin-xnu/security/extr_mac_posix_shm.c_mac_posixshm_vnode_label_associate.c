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
typedef  int /*<<< orphan*/  vnode_t ;
struct pshminfo {int dummy; } ;
struct label {int dummy; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PERFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pshminfo*,struct label*,int /*<<< orphan*/ ,struct label*) ; 
 int /*<<< orphan*/  vnode_label_associate_posixshm ; 

void
mac_posixshm_vnode_label_associate(kauth_cred_t cred,
	struct pshminfo *pshm, struct label *plabel,
	vnode_t vp, struct label *vlabel)
{
	MAC_PERFORM(vnode_label_associate_posixshm, cred, 
		    pshm, plabel, vp, vlabel);
}