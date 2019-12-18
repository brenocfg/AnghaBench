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
struct mibifa {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mibifa*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct mibifa*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mibifa_list ; 

__attribute__((used)) static void
destroy_ifa(struct mibifa *ifa)
{
	TAILQ_REMOVE(&mibifa_list, ifa, link);
	free(ifa);
}