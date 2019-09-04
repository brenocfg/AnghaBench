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
struct mptopt {int dummy; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int /*<<< orphan*/  bzero (struct mptopt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mptopt_zone ; 
 int /*<<< orphan*/  mptopt_zone_size ; 
 struct mptopt* zalloc (int /*<<< orphan*/ ) ; 
 struct mptopt* zalloc_noblock (int /*<<< orphan*/ ) ; 

struct mptopt *
mptcp_sopt_alloc(int how)
{
	struct mptopt *mpo;

	mpo = (how == M_WAITOK) ? zalloc(mptopt_zone) :
	    zalloc_noblock(mptopt_zone);
	if (mpo != NULL) {
		bzero(mpo, mptopt_zone_size);
	}

	return (mpo);
}