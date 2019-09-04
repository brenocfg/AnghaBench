#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vnop_write_args {TYPE_1__* a_vp; } ;
struct TYPE_2__ {int v_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISDIR ; 
#define  VDIR 128 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
devfs_write(struct vnop_write_args *ap)
        /* struct vnop_write_args  {
                struct vnode *a_vp;
                struct uio *a_uio;
                int  a_ioflag;
                kauth_cred_t a_cred;
        } */
{
	switch (ap->a_vp->v_type) {
	case VDIR:
		return(EISDIR);
	default:
		printf("devfs_write(): bad file type %d", ap->a_vp->v_type);
		return (EINVAL);
	}
}