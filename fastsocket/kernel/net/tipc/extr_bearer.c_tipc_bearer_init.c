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
struct media {int dummy; } ;
struct bearer {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAX_BEARERS ; 
 int /*<<< orphan*/  MAX_MEDIA ; 
 int /*<<< orphan*/ * kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * media_list ; 
 int /*<<< orphan*/ * tipc_bearers ; 
 int /*<<< orphan*/  tipc_net_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int tipc_bearer_init(void)
{
	int res;

	write_lock_bh(&tipc_net_lock);
	tipc_bearers = kcalloc(MAX_BEARERS, sizeof(struct bearer), GFP_ATOMIC);
	media_list = kcalloc(MAX_MEDIA, sizeof(struct media), GFP_ATOMIC);
	if (tipc_bearers && media_list) {
		res = 0;
	} else {
		kfree(tipc_bearers);
		kfree(media_list);
		tipc_bearers = NULL;
		media_list = NULL;
		res = -ENOMEM;
	}
	write_unlock_bh(&tipc_net_lock);
	return res;
}