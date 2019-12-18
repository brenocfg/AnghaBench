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
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ PFDEV_MAX ; 
 scalar_t__ PFDEV_PFM ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_lock ; 
 scalar_t__ pfdevcnt ; 

__attribute__((used)) static int
pfclose(dev_t dev, int flags, int fmt, struct proc *p)
{
#pragma unused(flags, fmt, p)
	if (minor(dev) >= PFDEV_MAX)
		return (ENXIO);

	if (minor(dev) == PFDEV_PFM) {
		lck_mtx_lock(pf_lock);
		VERIFY(pfdevcnt > 0);
		pfdevcnt--;
		lck_mtx_unlock(pf_lock);
	}
	return (0);
}