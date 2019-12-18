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
struct ft_tport {int /*<<< orphan*/  sess_count; } ;
struct ft_sess {int port_id; scalar_t__ params; int /*<<< orphan*/  hash; struct ft_tport* tport; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ft_sess_unhash(struct ft_sess *sess)
{
	struct ft_tport *tport = sess->tport;

	hlist_del_rcu(&sess->hash);
	BUG_ON(!tport->sess_count);
	tport->sess_count--;
	sess->port_id = -1;
	sess->params = 0;
}