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
struct mls_level {scalar_t__ sens; int /*<<< orphan*/  cat; } ;

/* Variables and functions */
 scalar_t__ ebitmap_contains (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_mls_enabled ; 

__attribute__((used)) static inline int mls_level_dom(struct mls_level *l1, struct mls_level *l2)
{
	if (!selinux_mls_enabled)
		return 1;

	return ((l1->sens >= l2->sens) &&
		ebitmap_contains(&l1->cat, &l2->cat));
}