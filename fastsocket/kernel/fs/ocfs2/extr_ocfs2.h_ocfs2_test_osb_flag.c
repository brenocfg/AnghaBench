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
struct ocfs2_super {unsigned long osb_flags; int /*<<< orphan*/  osb_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned long  ocfs2_test_osb_flag(struct ocfs2_super *osb,
						 unsigned long flag)
{
	unsigned long ret;

	spin_lock(&osb->osb_lock);
	ret = osb->osb_flags & flag;
	spin_unlock(&osb->osb_lock);
	return ret;
}