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
struct svc_cacherep {int /*<<< orphan*/  c_xid; int /*<<< orphan*/  c_hash; } ;

/* Variables and functions */
 scalar_t__ cache_hash ; 
 scalar_t__ hash_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maskbits ; 

__attribute__((used)) static void
hash_refile(struct svc_cacherep *rp)
{
	hlist_del_init(&rp->c_hash);
	hlist_add_head(&rp->c_hash, cache_hash + hash_32(rp->c_xid, maskbits));
}