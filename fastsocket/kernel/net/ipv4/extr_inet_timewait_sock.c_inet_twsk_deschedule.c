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
struct inet_timewait_sock {int dummy; } ;
struct inet_timewait_death_row {scalar_t__ tw_count; int /*<<< orphan*/  hashinfo; int /*<<< orphan*/  death_lock; int /*<<< orphan*/  tw_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __inet_twsk_kill (struct inet_timewait_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ inet_twsk_del_dead_node (struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  inet_twsk_put (struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void inet_twsk_deschedule(struct inet_timewait_sock *tw,
			  struct inet_timewait_death_row *twdr)
{
	spin_lock(&twdr->death_lock);
	if (inet_twsk_del_dead_node(tw)) {
		inet_twsk_put(tw);
		if (--twdr->tw_count == 0)
			del_timer(&twdr->tw_timer);
	}
	spin_unlock(&twdr->death_lock);
	__inet_twsk_kill(tw, twdr->hashinfo);
}