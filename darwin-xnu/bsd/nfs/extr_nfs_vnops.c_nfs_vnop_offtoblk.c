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
struct vnop_offtoblk_args {int a_offset; scalar_t__* a_lblkno; int /*<<< orphan*/  a_vp; } ;
struct nfsmount {int nm_biosize; } ;
typedef  scalar_t__ daddr64_t ;

/* Variables and functions */
 int ENXIO ; 
 struct nfsmount* VTONMP (int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 

int
nfs_vnop_offtoblk(
	struct vnop_offtoblk_args /* {
		struct vnodeop_desc *a_desc;
		vnode_t a_vp;
		off_t a_offset;
		daddr64_t *a_lblkno;
	} */ *ap)
{
	int biosize;
	vnode_t vp = ap->a_vp;
	struct nfsmount *nmp = VTONMP(vp);

	if (nfs_mount_gone(nmp))
		return (ENXIO);
	biosize = nmp->nm_biosize;

	*ap->a_lblkno = (daddr64_t)(ap->a_offset / biosize);

	return (0);
}