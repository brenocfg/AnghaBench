#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct inet_frags {TYPE_1__ secret_timer; scalar_t__ secret_interval; scalar_t__ rnd; int /*<<< orphan*/  lock; int /*<<< orphan*/ * hash; } ;

/* Variables and functions */
 int INETFRAGS_HASHSZ ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  inet_frag_secret_rebuild ; 
 int jiffies ; 
 int num_physpages ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_timer (TYPE_1__*,int /*<<< orphan*/ ,unsigned long) ; 

void inet_frags_init(struct inet_frags *f)
{
	int i;

	for (i = 0; i < INETFRAGS_HASHSZ; i++)
		INIT_HLIST_HEAD(&f->hash[i]);

	rwlock_init(&f->lock);

	f->rnd = (u32) ((num_physpages ^ (num_physpages>>7)) ^
				   (jiffies ^ (jiffies >> 6)));

	setup_timer(&f->secret_timer, inet_frag_secret_rebuild,
			(unsigned long)f);
	f->secret_timer.expires = jiffies + f->secret_interval;
	add_timer(&f->secret_timer);
}