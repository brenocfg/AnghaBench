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
struct nfsd4_session {struct nfs4_client* se_client; } ;
struct nfs4_client {int /*<<< orphan*/  cl_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  client_lock ; 
 int /*<<< orphan*/  free_client (struct nfs4_client*) ; 
 scalar_t__ is_client_expired (struct nfs4_client*) ; 
 int /*<<< orphan*/  renew_client_locked (struct nfs4_client*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
release_session_client(struct nfsd4_session *session)
{
	struct nfs4_client *clp = session->se_client;

	if (!atomic_dec_and_lock(&clp->cl_refcount, &client_lock))
		return;
	if (is_client_expired(clp)) {
		free_client(clp);
		session->se_client = NULL;
	} else
		renew_client_locked(clp);
	spin_unlock(&client_lock);
}