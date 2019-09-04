#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vnop_read_args {TYPE_3__* a_vp; int /*<<< orphan*/  a_context; int /*<<< orphan*/  a_uio; } ;
struct TYPE_5__ {int dn_access; } ;
typedef  TYPE_1__ devnode_t ;
struct TYPE_6__ {int v_type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  VDIR 128 
 int VNOP_READDIR (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* VTODN (TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
devfs_read(struct vnop_read_args *ap)
        /* struct vnop_read_args {
                struct vnode *a_vp;
                struct uio *a_uio;
                int  a_ioflag;
		vfs_context_t a_context;
        } */
{
    	devnode_t * dn_p = VTODN(ap->a_vp);

	switch (ap->a_vp->v_type) {
	  case VDIR: {
	      dn_p->dn_access = 1;

	      return VNOP_READDIR(ap->a_vp, ap->a_uio, 0, NULL, NULL, ap->a_context);
	  }
	  default: {
	      printf("devfs_read(): bad file type %d", ap->a_vp->v_type);
	      return(EINVAL);
	  }
	}
}