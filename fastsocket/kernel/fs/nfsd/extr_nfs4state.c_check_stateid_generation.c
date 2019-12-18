#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ si_generation; } ;
typedef  TYPE_1__ stateid_t ;

/* Variables and functions */
 int HAS_SESSION ; 
 int nfs_ok ; 
 int nfserr_bad_stateid ; 
 int nfserr_old_stateid ; 

__attribute__((used)) static int check_stateid_generation(stateid_t *in, stateid_t *ref, int flags)
{
	/*
	 * When sessions are used the stateid generation number is ignored
	 * when it is zero.
	 */
	if ((flags & HAS_SESSION) && in->si_generation == 0)
		goto out;

	/* If the client sends us a stateid from the future, it's buggy: */
	if (in->si_generation > ref->si_generation)
		return nfserr_bad_stateid;
	/*
	 * The following, however, can happen.  For example, if the
	 * client sends an open and some IO at the same time, the open
	 * may bump si_generation while the IO is still in flight.
	 * Thanks to hard links and renames, the client never knows what
	 * file an open will affect.  So it could avoid that situation
	 * only by serializing all opens and IO from the same open
	 * owner.  To recover from the old_stateid error, the client
	 * will just have to retry the IO:
	 */
	if (in->si_generation < ref->si_generation)
		return nfserr_old_stateid;
out:
	return nfs_ok;
}