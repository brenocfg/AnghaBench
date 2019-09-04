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
struct in6_multi_mship {int /*<<< orphan*/ * i6mm_maddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN6M_REMREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in6_mc_leave (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in6_multi_mship_free (struct in6_multi_mship*) ; 

int
in6_leavegroup(struct in6_multi_mship *imm)
{
	if (imm->i6mm_maddr != NULL) {
		in6_mc_leave(imm->i6mm_maddr, NULL);
		IN6M_REMREF(imm->i6mm_maddr);
		imm->i6mm_maddr = NULL;
	}
	in6_multi_mship_free(imm);
	return 0;
}