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
struct svc_fh {TYPE_1__* fh_export; } ;
struct TYPE_2__ {int ex_flags; } ;

/* Variables and functions */
 int NFSEXP_MSNFS ; 

__attribute__((used)) static inline int svc_msnfs(struct svc_fh *ffhp)
{
#ifdef MSNFS
	return (ffhp->fh_export->ex_flags & NFSEXP_MSNFS);
#else
	return 0;
#endif
}