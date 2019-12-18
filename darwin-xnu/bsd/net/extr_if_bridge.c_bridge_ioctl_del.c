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
struct ifbreq {int /*<<< orphan*/  ifbr_ifsname; } ;
struct bridge_softc {int dummy; } ;
struct bridge_iflist {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  bridge_delete_member (struct bridge_softc*,struct bridge_iflist*,int /*<<< orphan*/ ) ; 
 struct bridge_iflist* bridge_lookup_member (struct bridge_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bridge_ioctl_del(struct bridge_softc *sc, void *arg)
{
	struct ifbreq *req = arg;
	struct bridge_iflist *bif;

	bif = bridge_lookup_member(sc, req->ifbr_ifsname);
	if (bif == NULL)
		return (ENOENT);

	bridge_delete_member(sc, bif, 0);

	return (0);
}