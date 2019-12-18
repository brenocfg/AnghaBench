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
struct nlm_share {struct nlm_share* s_next; int /*<<< orphan*/  s_host; } ;
struct nlm_host {int dummy; } ;
struct nlm_file {struct nlm_share* f_shares; } ;
typedef  scalar_t__ (* nlm_host_match_fn_t ) (int /*<<< orphan*/ ,struct nlm_host*) ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nlm_share*) ; 

void nlmsvc_traverse_shares(struct nlm_host *host, struct nlm_file *file,
		nlm_host_match_fn_t match)
{
	struct nlm_share	*share, **shpp;

	shpp = &file->f_shares;
	while ((share = *shpp) !=  NULL) {
		if (match(share->s_host, host)) {
			*shpp = share->s_next;
			kfree(share);
			continue;
		}
		shpp = &share->s_next;
	}
}