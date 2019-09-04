#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* nfsnode_t ;
struct TYPE_6__ {TYPE_1__* n_cookiecache; scalar_t__ n_cookieverf; scalar_t__ n_eofcookie; } ;
struct TYPE_5__ {int mru; int /*<<< orphan*/  next; scalar_t__ free; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSNUMCOOKIES ; 
 int /*<<< orphan*/  NFSTOV (TYPE_2__*) ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_vtype (int /*<<< orphan*/ ) ; 

void
nfs_invaldir(nfsnode_t dnp)
{
	if (vnode_vtype(NFSTOV(dnp)) != VDIR)
		return;
	dnp->n_eofcookie = 0;
	dnp->n_cookieverf = 0;
	if (!dnp->n_cookiecache)
		return;
	dnp->n_cookiecache->free = 0;
	dnp->n_cookiecache->mru = -1;
	memset(dnp->n_cookiecache->next, -1, NFSNUMCOOKIES);
}