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
struct ipath_pd {int dummy; } ;
struct ipath_ibdev {int /*<<< orphan*/  n_pds_lock; int /*<<< orphan*/  n_pds_allocated; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ipath_pd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct ipath_ibdev* to_idev (int /*<<< orphan*/ ) ; 
 struct ipath_pd* to_ipd (struct ib_pd*) ; 

__attribute__((used)) static int ipath_dealloc_pd(struct ib_pd *ibpd)
{
	struct ipath_pd *pd = to_ipd(ibpd);
	struct ipath_ibdev *dev = to_idev(ibpd->device);

	spin_lock(&dev->n_pds_lock);
	dev->n_pds_allocated--;
	spin_unlock(&dev->n_pds_lock);

	kfree(pd);

	return 0;
}