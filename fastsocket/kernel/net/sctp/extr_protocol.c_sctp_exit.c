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
struct sctp_hashbucket {int dummy; } ;
struct sctp_bind_hashbucket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_sctp_mibs () ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 
 int /*<<< orphan*/  inet_ctl_sock_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int sctp_assoc_hashsize ; 
 scalar_t__ sctp_assoc_hashtable ; 
 int /*<<< orphan*/  sctp_bucket_cachep ; 
 int /*<<< orphan*/  sctp_chunk_cachep ; 
 int /*<<< orphan*/  sctp_ctl_sock ; 
 int /*<<< orphan*/  sctp_dbg_objcnt_exit () ; 
 int /*<<< orphan*/  sctp_ep_hashtable ; 
 int /*<<< orphan*/  sctp_free_local_addr_list () ; 
 int sctp_port_hashsize ; 
 scalar_t__ sctp_port_hashtable ; 
 int /*<<< orphan*/  sctp_proc_exit () ; 
 int /*<<< orphan*/  sctp_sysctl_unregister () ; 
 int /*<<< orphan*/  sctp_v4_del_protocol () ; 
 int /*<<< orphan*/  sctp_v4_pf_exit () ; 
 int /*<<< orphan*/  sctp_v4_protosw_exit () ; 
 int /*<<< orphan*/  sctp_v6_del_protocol () ; 
 int /*<<< orphan*/  sctp_v6_pf_exit () ; 
 int /*<<< orphan*/  sctp_v6_protosw_exit () ; 

void sctp_exit(void)
{
	/* BUG.  This should probably do something useful like clean
	 * up all the remaining associations and all that memory.
	 */

	/* Unregister with inet6/inet layers. */
	sctp_v6_del_protocol();
	sctp_v4_del_protocol();

	/* Free the control endpoint.  */
	inet_ctl_sock_destroy(sctp_ctl_sock);

	/* Free protosw registrations */
	sctp_v6_protosw_exit();
	sctp_v4_protosw_exit();

	/* Free the local address list.  */
	sctp_free_local_addr_list();

	/* Unregister with socket layer. */
	sctp_v6_pf_exit();
	sctp_v4_pf_exit();

	sctp_sysctl_unregister();

	free_pages((unsigned long)sctp_assoc_hashtable,
		   get_order(sctp_assoc_hashsize *
			     sizeof(struct sctp_hashbucket)));
	kfree(sctp_ep_hashtable);
	free_pages((unsigned long)sctp_port_hashtable,
		   get_order(sctp_port_hashsize *
			     sizeof(struct sctp_bind_hashbucket)));

	sctp_dbg_objcnt_exit();
	sctp_proc_exit();
	cleanup_sctp_mibs();

	rcu_barrier(); /* Wait for completion of call_rcu()'s */

	kmem_cache_destroy(sctp_chunk_cachep);
	kmem_cache_destroy(sctp_bucket_cachep);
}