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
struct v9fs_session_info {int /*<<< orphan*/ * fscache; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_FSC ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,struct v9fs_session_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_relinquish_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void v9fs_cache_session_put_cookie(struct v9fs_session_info *v9ses)
{
	P9_DPRINTK(P9_DEBUG_FSC, "session %p put cookie %p", v9ses,
		   v9ses->fscache);
	fscache_relinquish_cookie(v9ses->fscache, 0);
	v9ses->fscache = NULL;
}