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
struct gfs2_holder {int /*<<< orphan*/  gh_iflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_WAIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfs2_holder_wake(struct gfs2_holder *gh)
{
	clear_bit(HIF_WAIT, &gh->gh_iflags);
	smp_mb__after_clear_bit();
	wake_up_bit(&gh->gh_iflags, HIF_WAIT);
}