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
struct dentry {int dummy; } ;
struct autofs_info {scalar_t__ last_used; } ;

/* Variables and functions */
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 scalar_t__ now ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline int autofs4_can_expire(struct dentry *dentry,
					unsigned long timeout, int do_now)
{
	struct autofs_info *ino = autofs4_dentry_ino(dentry);

	/* dentry in the process of being deleted */
	if (ino == NULL)
		return 0;

	if (!do_now) {
		/* Too young to die */
		if (!timeout || time_after(ino->last_used + timeout, now))
			return 0;

		/* update last_used here :-
		   - obviously makes sense if it is in use now
		   - less obviously, prevents rapid-fire expire
		     attempts if expire fails the first time */
		ino->last_used = now;
	}
	return 1;
}