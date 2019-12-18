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
struct nfs_cache_defer_req {int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int nfs_cache_getent_timeout ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

int nfs_cache_wait_for_upcall(struct nfs_cache_defer_req *dreq)
{
	if (wait_for_completion_timeout(&dreq->completion,
			nfs_cache_getent_timeout * HZ) == 0)
		return -ETIMEDOUT;
	return 0;
}