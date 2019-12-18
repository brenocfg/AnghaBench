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
struct thin_c {int /*<<< orphan*/  retry_on_resume_list; int /*<<< orphan*/  deferred_bio_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  requeue_bio_list (struct thin_c*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void requeue_io(struct thin_c *tc)
{
	requeue_bio_list(tc, &tc->deferred_bio_list);
	requeue_bio_list(tc, &tc->retry_on_resume_list);
}