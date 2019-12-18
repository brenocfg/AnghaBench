#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; } ;
struct mpoa_client {int /*<<< orphan*/  ingress_lock; struct in_cache_entry* in_cache; } ;
struct TYPE_4__ {int tv_sec; } ;
struct TYPE_3__ {int holding_time; } ;
struct in_cache_entry {scalar_t__ entry_state; int refresh_time; struct in_cache_entry* next; TYPE_2__ reply_wait; TYPE_1__ ctrl_info; } ;

/* Variables and functions */
 scalar_t__ INGRESS_REFRESHING ; 
 scalar_t__ INGRESS_RESOLVED ; 
 int /*<<< orphan*/  ddprintk (char*) ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void refresh_entries(struct mpoa_client *client)
{
	struct timeval now;
	struct in_cache_entry *entry = client->in_cache;

	ddprintk("mpoa: mpoa_caches.c: refresh_entries\n");
	do_gettimeofday(&now);

	read_lock_bh(&client->ingress_lock);
	while( entry != NULL ){
		if( entry->entry_state == INGRESS_RESOLVED ){
			if(!(entry->refresh_time))
				entry->refresh_time = (2*(entry->ctrl_info.holding_time))/3;
			if( (now.tv_sec - entry->reply_wait.tv_sec) > entry->refresh_time ){
				dprintk("mpoa: mpoa_caches.c: refreshing an entry.\n");
				entry->entry_state = INGRESS_REFRESHING;

			}
		}
		entry = entry->next;
	}
	read_unlock_bh(&client->ingress_lock);
}