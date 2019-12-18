#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v9fs_session_info {int /*<<< orphan*/  fscache; int /*<<< orphan*/  cachetag; } ;
struct TYPE_2__ {int /*<<< orphan*/  primary_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_FSC ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,struct v9fs_session_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_acquire_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v9fs_session_info*) ; 
 TYPE_1__ v9fs_cache_netfs ; 
 int /*<<< orphan*/  v9fs_cache_session_index_def ; 
 int /*<<< orphan*/  v9fs_random_cachetag (struct v9fs_session_info*) ; 

void v9fs_cache_session_get_cookie(struct v9fs_session_info *v9ses)
{
	/* If no cache session tag was specified, we generate a random one. */
	if (!v9ses->cachetag)
		v9fs_random_cachetag(v9ses);

	v9ses->fscache = fscache_acquire_cookie(v9fs_cache_netfs.primary_index,
						&v9fs_cache_session_index_def,
						v9ses);
	P9_DPRINTK(P9_DEBUG_FSC, "session %p get cookie %p", v9ses,
		   v9ses->fscache);
}