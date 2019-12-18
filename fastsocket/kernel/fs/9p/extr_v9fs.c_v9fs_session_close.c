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
struct v9fs_session_info {int /*<<< orphan*/  slist; int /*<<< orphan*/  aname; int /*<<< orphan*/  uname; int /*<<< orphan*/  cachetag; scalar_t__ fscache; int /*<<< orphan*/ * clnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __putname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p9_client_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_cache_session_put_cookie (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  v9fs_sessionlist_lock ; 

void v9fs_session_close(struct v9fs_session_info *v9ses)
{
	if (v9ses->clnt) {
		p9_client_destroy(v9ses->clnt);
		v9ses->clnt = NULL;
	}

#ifdef CONFIG_9P_FSCACHE
	if (v9ses->fscache) {
		v9fs_cache_session_put_cookie(v9ses);
		kfree(v9ses->cachetag);
	}
#endif
	__putname(v9ses->uname);
	__putname(v9ses->aname);

	spin_lock(&v9fs_sessionlist_lock);
	list_del(&v9ses->slist);
	spin_unlock(&v9fs_sessionlist_lock);
}