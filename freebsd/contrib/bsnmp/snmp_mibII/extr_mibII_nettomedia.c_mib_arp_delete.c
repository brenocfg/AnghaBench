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
struct mibarp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mibarp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct mibarp*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mibarp_list ; 

void
mib_arp_delete(struct mibarp *at)
{
	TAILQ_REMOVE(&mibarp_list, at, link);
	free(at);
}