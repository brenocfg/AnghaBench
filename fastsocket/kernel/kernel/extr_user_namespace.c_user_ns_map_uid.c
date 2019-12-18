#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct user_namespace {TYPE_1__* creator; } ;
struct cred {TYPE_1__* user; } ;
struct TYPE_2__ {struct user_namespace* user_ns; } ;

/* Variables and functions */
 struct user_namespace init_user_ns ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  overflowuid ; 

uid_t user_ns_map_uid(struct user_namespace *to, const struct cred *cred, uid_t uid)
{
	struct user_namespace *tmp;

	if (likely(to == cred->user->user_ns))
		return uid;


	/* Is cred->user the creator of the target user_ns
	 * or the creator of one of it's parents?
	 */
	for ( tmp = to; tmp != &init_user_ns;
	      tmp = tmp->creator->user_ns ) {
		if (cred->user == tmp->creator) {
			return (uid_t)0;
		}
	}

	/* No useful relationship so no mapping */
	return overflowuid;
}