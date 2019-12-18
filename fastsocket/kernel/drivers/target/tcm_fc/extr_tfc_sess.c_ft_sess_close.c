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
typedef  int u32 ;
struct se_session {struct ft_sess* fabric_sess_ptr; } ;
struct ft_sess {int port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ft_lport_lock ; 
 int /*<<< orphan*/  ft_sess_put (struct ft_sess*) ; 
 int /*<<< orphan*/  ft_sess_unhash (struct ft_sess*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  transport_deregister_session_configfs (struct se_session*) ; 

void ft_sess_close(struct se_session *se_sess)
{
	struct ft_sess *sess = se_sess->fabric_sess_ptr;
	u32 port_id;

	mutex_lock(&ft_lport_lock);
	port_id = sess->port_id;
	if (port_id == -1) {
		mutex_unlock(&ft_lport_lock);
		return;
	}
	pr_debug("port_id %x\n", port_id);
	ft_sess_unhash(sess);
	mutex_unlock(&ft_lport_lock);
	transport_deregister_session_configfs(se_sess);
	ft_sess_put(sess);
	/* XXX Send LOGO or PRLO */
	synchronize_rcu();		/* let transport deregister happen */
}