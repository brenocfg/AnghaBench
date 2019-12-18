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
struct utrace {int resume; int /*<<< orphan*/  lock; scalar_t__ pending_attach; } ;
typedef  enum utrace_resume_action { ____Placeholder_utrace_resume_action } utrace_resume_action ;

/* Variables and functions */
 int UTRACE_INTERRUPT ; 
 int UTRACE_RESUME ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  splice_attaching (struct utrace*) ; 

__attribute__((used)) static enum utrace_resume_action start_report(struct utrace *utrace)
{
	enum utrace_resume_action resume = utrace->resume;
	if (utrace->pending_attach ||
	    (resume > UTRACE_INTERRUPT && resume < UTRACE_RESUME)) {
		spin_lock(&utrace->lock);
		splice_attaching(utrace);
		resume = utrace->resume;
		if (resume > UTRACE_INTERRUPT)
			utrace->resume = UTRACE_RESUME;
		spin_unlock(&utrace->lock);
	}
	return resume;
}