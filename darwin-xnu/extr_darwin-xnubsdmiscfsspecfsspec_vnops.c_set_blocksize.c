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
struct vnode {int v_specsize; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int (* d_psize ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 void* DEV_BSIZE ; 
 TYPE_1__* bdevsw ; 
 size_t major (int /*<<< orphan*/ ) ; 
 size_t nblkdev ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_blocksize(struct vnode *vp, dev_t dev)
{
    int (*size)(dev_t);
    int rsize;

    if ((major(dev) < nblkdev) && (size = bdevsw[major(dev)].d_psize)) {
        rsize = (*size)(dev);
	if (rsize <= 0)        /* did size fail? */
	    vp->v_specsize = DEV_BSIZE;
	else
	    vp->v_specsize = rsize;
    }
    else
	    vp->v_specsize = DEV_BSIZE;
}