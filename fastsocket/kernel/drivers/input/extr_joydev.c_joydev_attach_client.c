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
struct joydev_client {int /*<<< orphan*/  node; } ;
struct joydev {int /*<<< orphan*/  client_lock; int /*<<< orphan*/  client_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void joydev_attach_client(struct joydev *joydev,
				 struct joydev_client *client)
{
	spin_lock(&joydev->client_lock);
	list_add_tail_rcu(&client->node, &joydev->client_list);
	spin_unlock(&joydev->client_lock);
	synchronize_rcu();
}